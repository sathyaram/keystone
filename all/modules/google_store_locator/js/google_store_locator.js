;(function ($, Drupal, window, document, undefined) {
  // module global namespace
  Drupal.GSL = Drupal.GSL || {};

  Drupal.GSL.currentMap = Drupal.GSL.currentMap || {};
  Drupal.GSL.currentCluster = Drupal.GSL.currentCluster || {};

  // Global Geocoder instance, for convenience.
  Drupal.GSL.geocoder = new google.maps.Geocoder;

  /**
   * Set the current map.
   */
  Drupal.GSL.setCurrentMap = function(map, mapid) {
    Drupal.GSL.currentMap = map;
    Drupal.GSL.currentMap.mapid = mapid;
  };

  /**
   * Get the current map
   */
  Drupal.GSL.getCurrentMap = function(view) {
    if (view) {
      return view.getMap();
    }

    return Drupal.GSL.currentMap || {};
  };

  /**
   * Remove a marker from the map.
   */
  Drupal.GSL.removeMarker = function(marker) {
    if (marker instanceof google.maps.Marker) {
      marker.setMap(null);
      marker.unbindAll();
    }
  };

  /**
   * @extends storeLocator.StaticDataFeed
   * @constructor
   */
  Drupal.GSL.dataSource = function (datapath) {
    this.parent = Drupal.GSL.dataSource.parent;
    // call the parent constructor
    this.parent.call(this);

    // initialize variables
    this._datapath = datapath;
    this._stores = [];
    this._storesCache = [];

    // The parent class calls this but sets this.firstCallback_ in it's
    // getStores() which would be minified and is now overridden by a custom
    // getStores().
    // if (this.firstCallback_) {
    //   this.firstCallback_();
    // } else {
    //   delete this.firstCallback_;
    // }
  };

  // Set parent class
  Drupal.GSL.dataSource.parent = storeLocator.StaticDataFeed;

  // Inherit parent's prototype
  Drupal.GSL.dataSource.prototype = Object.create(Drupal.GSL.dataSource.parent.prototype);

  // Correct the constructor pointer
  Drupal.GSL.dataSource.prototype.constructor = Drupal.GSL.dataSource;

  /**
   * Retrieves the parsed stores cached for a given url.
   */
  Drupal.GSL.dataSource.prototype.getStoresCache = function(url) {
    for (var i = 0; i < this._storesCache.length; i++) {
      if (this._storesCache[i].url == url) {
        return ('stores' in this._storesCache[i]) ? this._storesCache[i].stores : [];
      }
    }

    return [];
  };

  /**
   * Retrieves the parsed stores cached for a given url.
   */
  Drupal.GSL.dataSource.prototype.getStoresCacheIndex = function(url) {
    for (var i = 0; i < this._storesCache.length; i++) {
      if (this._storesCache[i].url == url) {
        return i;
      }
    }

    return -1;
  };

  /**
   * Sets the parsed stores cached for a given url.
   */
  Drupal.GSL.dataSource.prototype.setStoresCache = function(url, stores) {
    if (this._storesCache.length == 3) {
      var expiredCache = this._storesCache.shift();
    }

    this._storesCache.push({'url': url, 'stores': stores});
    return this;
  };

  /**
   * Sets the parsed stores cached for a given url.
   */
  Drupal.GSL.dataSource.prototype.clearStoresCache = function(url) {
    if (url) {
      var urlIndex = this.getStoresCacheIndex(url);
      if (urlIndex > -1) {
        this._storesCache.splice(urlIndex, 1);
      }
    }
    else {
      this._storesCache = [];
    }

    return this;
  };

  /**
   * Overrides getStores().
   */
  Drupal.GSL.dataSource.prototype.getStores = function(bounds, features, callback, centerPoint) {
    // Prevent race condition - if getStores is called before stores are
    // loaded.
    // Parent class does this so it might be needed here.
    // if (!this._stores.length) {
    //  var that = this;
    //  this.firstCallback_ = function() {
    //    that.getStores(bounds, features, callback);
    //  };
    //  return;
    // }

    var gslSettings = Drupal.settings.gsl[Drupal.GSL.currentMap.mapid];
    var dataCacheEnabled = gslSettings['dataCacheEnabled'];
    var markerClusterEnabled = gslSettings['mapcluster'];
    var markerClusterZoom = gslSettings['mapclusterzoom'];
    var switchToMarkerCluster = (Drupal.GSL.currentMap.getZoom() < markerClusterZoom);
    var viewportEnabled = gslSettings['viewportManage'];
    var viewportMarkerLimit = gslSettings['viewportMarkerLimit'];
    var viewportNoMarkers = (Drupal.GSL.currentMap.getZoom() < viewportMarkerLimit);

    if ((markerClusterEnabled && switchToMarkerCluster && !$.isEmptyObject(Drupal.GSL.currentCluster)) || (viewportEnabled && viewportNoMarkers)) {
      // Once cluster has been initialized we don't even need to fetch data, or
      // if Viewport is enabled, and the map zoom is less then the viewport zoom
      // limit.
      return;
    }

    if (!viewportEnabled) {
      // Viewport marker management isn't enabled. We're gonna load all the
      // stores.
      var url = this._datapath;
    }
    else {
      // Marker management is enabled. Load only some of the stores.
      var swPoint = bounds.getSouthWest();
      var nePoint = bounds.getNorthEast();

      var swLat = swPoint.lat();
      var swLng = swPoint.lng();
      var neLat = nePoint.lat();
      var neLng = nePoint.lng();
      if (swLat < neLat) {
        var latRange = swLat + '--' + neLat;
      }
      else {
        // This case is never triggered since the Google Map doesn't allow you to revolve vertically
        var latRange = swLat + '--90+-90--' + neLat;
      }
      if (swLng < neLng) {
        var lonRange = swLng + '--' + neLng;
      }
      else {
        var lonRange = swLng + '--180+-180--' + neLng;
      }

      var url = this._datapath + '/' + latRange + '/' + lonRange;
    }

    var that = this;

    var cachedStores = this.getStoresCache(url);
    if (dataCacheEnabled && cachedStores.length > 0) {
      // If cache is enabled and url in cache.
      this.processParsedStores(cachedStores, bounds, features, callback, centerPoint);
    }
    else {
      // Loading all stores can take a while, display a loading overlay.
      if ($("#cluster-loading").length == 0) {
        $('#' + Drupal.GSL.currentMap.mapid).append('<div id="cluster-loading" class="ajax-progress ajax-progress-throbber"><div>' + Drupal.t('Loading') + '<span class="throbber"></span></div></div>');
      }
      $.getJSON(url, function(json) {
        //defining our success handler, i.e. if the path we're passing to $.getJSON
        //is legit and returns a JSON file then this runs.

        // These will be either all stores, or those within the viewport.
        var parsedStores = that.parseStores_(json);
        that.setStoresCache(url, parsedStores);
        that.processParsedStores(parsedStores, bounds, features, callback, centerPoint);
        $("#cluster-loading").remove();
      });
    }
  };

  /**
   * Process parsed stores.
   */
  Drupal.GSL.dataSource.prototype.processParsedStores = function(stores, bounds, features, callback, centerPoint) {
    if (stores && stores.length > 0) {
      var that = this;
      var gslSettings = Drupal.settings.gsl[Drupal.GSL.currentMap.mapid];
      var markerClusterEnabled = gslSettings['mapcluster'];
      var markerClusterZoom = gslSettings['mapclusterzoom'];
      var switchToMarkerCluster = (Drupal.GSL.currentMap.getZoom() < markerClusterZoom);

      // Filter stores for features.
      var filtered_stores = [];
      for (var i = 0, store; store = stores[i]; i++) {
        if (store.hasAllFeatures(features)) {
          filtered_stores.push(store);
        }
      }

      if (centerPoint && (centerPoint instanceof google.maps.LatLng)) {
        this.sortByDistance_(centerPoint, filtered_stores);
      }
      else {
        this.sortByDistance_(bounds.getCenter(), filtered_stores);
      }

      if (markerClusterEnabled && switchToMarkerCluster) {
        if ($.isEmptyObject(Drupal.GSL.currentCluster)) {
          Drupal.GSL.initializeCluster(filtered_stores, that);
        }
      }

      // The callback sets the stores on the main object.
      callback(filtered_stores);
    }
  };

  /**
   * Overridden: Sorts a list of given stores by distance from a point in ascending order.
   * Directly manipulates the given array (has side effects).
   * @private
   * @param {google.maps.LatLng} latLng the point to sort from.
   * @param {!Array.<!storeLocator.Store>} stores  the stores to sort.
   */
  Drupal.GSL.dataSource.prototype.sortByDistance_ = function(latLng, stores) {
    stores.sort(function(a, b) {
      return a.distanceTo(latLng) - b.distanceTo(latLng);
    });
  };

  /**
   * Overridden: Set the stores for this data feed.
   * @param {!Array.<!storeLocator.Store>} stores the stores for this data feed.
   *
   * - Sets _stores since storeLocator variable is minified
   */
  Drupal.GSL.dataSource.prototype.setStores = function(stores) {
    this._stores = stores;
    this.parent.prototype.setStores.apply(this, arguments);
  };

  /**
   * Parse data feed
   * @param {object} JSON
   * @return {!Array.<!storeLocator.Store>}
   */
  Drupal.GSL.dataSource.prototype.parseStores_ = function(json) {
    var stores = [];
    if (!('features' in json)) {
      return stores;
    }

    // build all our stores
    for (var i = 0; i < json.features.length; i++) {

      var item = json.features[i];

      if (!item) {
        continue;
      }

      // clone item properties so we can alter for features
      var itemFeatures = ('properties' in item) ? $.extend({}, item.properties) : {};

      // initialize store properties
      var storeProps = {};

      // extract coordinates
      var Xcoord = item.geometry.coordinates[0];
      var Ycoord = item.geometry.coordinates[1];

      // create a unique id
      var store_id = '';

      if (itemFeatures.uniqueid) {
        // Allow the response to provide an id.
        store_id = itemFeatures.uniqueid;
      }
      else if (itemFeatures.nid) {
        // Legacy support: nid field name.
        store_id = itemFeatures.nid;
      }
      else if (itemFeatures.Nid) {
        // Legacy support: Nid Label.
        store_id = itemFeatures.Nid;
      }
      else {
        store_id = this.uniqueStoreId();
      }

      // Prepend store to ensure it's a valid id name.
      store_id = 'store-' + store_id;

      // set title to views_geojson 'name'
      if ('name' in itemFeatures) {
        storeProps.title = itemFeatures.name;
        delete itemFeatures.name;
      }
      else {
        storeProps.title = store_id;
      }

      // set address to views_geojson 'description'
      if ('description' in itemFeatures) {
        storeProps.address = itemFeatures.description;
        delete itemFeatures.description;
      }

      // set latitude and longitude
      var position = new google.maps.LatLng(Ycoord, Xcoord);

      // create a FeatureSet since features are required by storeLocator.Store()
      var storeFeatureSet = new storeLocator.FeatureSet;
      for (var prop in itemFeatures) {
        // only add rendered features
        if (prop.search(/_rendered$/i) > 0 && itemFeatures[prop]) {
          switch(prop) {
            case "gsl_feature_filter_list_rendered":
              // It's a non-empty feature filter list. We need to create an id and
              // display name for it. It will be coming in as a comma separated
              // string.
              var list = itemFeatures[prop].split(',');
              for(var j = 0; j < list.length; j++) {
                // Go through each feature and add it.
                var label = list[j].trim();
                // Generate the id from the label by getting rid of all the
                // whitespace in it.
                var id = label.replace(/\s/g,'');
                var storeFeature = new storeLocator.Feature(id, label);
                storeFeatureSet.add(storeFeature);
              }
              break;

            case "gsl_props_misc_rendered":
              storeProps.misc = itemFeatures.gsl_props_misc_rendered;
              break;

            case "gsl_props_phone_rendered":
              storeProps.phone = itemFeatures.gsl_props_phone_rendered;
              break;

            case "gsl_props_web_rendered":
              var url = itemFeatures.gsl_props_web_rendered.split(',');
              storeProps.web = '<a href="' + url[1] + '">' + url[0] + '</a>';
              break;

          }
        }
      }
      // create our new store
      var store = new storeLocator.Store(store_id, position, storeFeatureSet, storeProps);
      stores.push(store);
    }

    return stores;
  };

  /**
   * Generate a unique id for a store.
   * @ref: http://stackoverflow.com/questions/105034/how-to-create-a-guid-uuid-in-javascript
   */
  Drupal.GSL.dataSource.prototype.uniqueStoreId = function(store) {
    function s4() {
      return Math.floor((1 + Math.random()) * 0x10000)
                 .toString(16)
                 .substring(1);
    }

    return s4() + s4() + '-' + s4() + '-' + s4() + '-' + s4() + '-' + s4() + s4() + s4();
  };

  /**
   * @extends storeLocator.Panel
   * @constructor
   */
  Drupal.GSL.Panel = function (el, opt_options) {
    var that = this;
    this.parent = Drupal.GSL.Panel.parent;
    this.panelElement = el;
    this.searchMarker = null;
    this._searchIsLocked = false;

    this.settings = $.extend({
      'locationSearch': true,
      'locationSearchLabel': 'Where are you?',
      'featureFilter': true,
      'directions': true,
      'view': null
    }, opt_options);


    // set items per panel
    if (opt_options['items_per_panel'] && !isNaN(opt_options['items_per_panel'])) {
      this.set('items_per_panel', opt_options['items_per_panel']);
    }
    else {
      // use default items per panel
      this.set('items_per_panel', Drupal.GSL.Panel.ITEMS_PER_PANEL_DEFAULT);
    }

    // call the parent constructor (in compiled format).
    var parentOptions = $.extend(opt_options, {
      'locationSearch': false,
    });
    this.parent.call(this, el, parentOptions);

    // ensure this variable is set
    this.storeList_ = $('.store-list', el);

    // Get filter element if set up in parent.
    this.filterElement = this.filter_ = $('form.storelocator-filter', el);

    if (this.filter_.length) {
      this.featureFilter_ = $('.feature-filter', this.filter_);

      // Override search events to control map zoom.
      // The base class's "geocode" listener does a fitBounds() and setZoom(13).
      if (this.settings['locationSearch']) {
        this.locationSearchElement = this.locationSearch_ = $('<div class="location-search"><h4>' + this.settings['locationSearchLabel'] + '</h4><input></div>');
        this.filter_.prepend(this.locationSearchElement);

        if (typeof google.maps.places != 'undefined') {
          this.initAutocomplete_();
        }
        else {
          this.filter_.submit(function() {
            if (!that.isSearchLocked()) {
              var searchText = $('input', that.locationSearchElement).val();
              // Create a fake place similar to autocomplete.
              var place = {'name': searchText};
              google.maps.event.trigger(that, 'searchChanged', place);
            }
          });
        }

        // Kill default action.
        this.filter_.submit(function() {
          return false;
        });

        // Add listener for searchChanged.
        google.maps.event.addListener(this, 'searchChanged', function(place, zoom) {
          this.searchChanged(place, zoom);
        });
      }
    }

    // Directions overridden since this get set in the "geocode" listener.
    if (this.settings['directions']) {
      this.directionsRenderer_ = new google.maps.DirectionsRenderer({
        draggable: true
      });
      this.directionsService_ = new google.maps.DirectionsService;
      this.directionsVisible_ = false;

      this.directionsPanel_ = $('.directions-panel', this.el);
      if (this.directionsPanel_.length) {
        // Override form submit to be this classes function.
        this.directionsPanel_.find('form')
          .unbind('submit')
          .submit(function() {
            that.renderDirections_();
            return false;
          });
      }
    }
  };

  // Set parent class
  Drupal.GSL.Panel.parent = storeLocator.Panel;

  // Extend object.
  Drupal.GSL.Panel.prototype = Object.create(Drupal.GSL.Panel.parent.prototype);

  // Correct the constructor pointer.
  Drupal.GSL.Panel.prototype.constructor = Drupal.GSL.Panel;

  Drupal.GSL.Panel.ITEMS_PER_PANEL_DEFAULT = 10;

  /**
   * Returns the value of the map setting as passed to the Panel class.
   */
  Drupal.GSL.Panel.prototype.getMapSetting = function(name) {
    if (this.settings && this.settings.mapSettings && (name in this.settings.mapSettings)) {
      return this.settings.mapSettings[name];
    }

    return null;
  };

  /**
   * Get the zoom level for the location search.
   */
  Drupal.GSL.Panel.prototype.getSearchZoomLevel = function() {
    var searchZoom = this.getMapSetting('loc_search_zoom');
    if (isFinite(searchZoom)) {
      return searchZoom;
    }

    var locAwareZoom = this.getMapSetting('loc_aware_zoom');
    if (isFinite(locAwareZoom)) {
      return locAwareZoom;
    }

    return undefined;
  };

  /**
   * Override initAutocomplete_()
   */
  Drupal.GSL.Panel.prototype.initAutocomplete_ = function() {
    var that = this;
    var $input = $('input', this.locationSearchElement);
    var input = $input[0];

    this.autoCompleteHandler = new google.maps.places.Autocomplete(input);
    if (this.get('view')) {
      this.autoCompleteHandler.bindTo('bounds', this.get('view').getMap());
    }

    // Listen for autocomplete places changed.
    // This occurs when a user selects an item from the drop down or hits enter.
    google.maps.event.addListener(this.autoCompleteHandler, 'place_changed', function() {
      if (!that.isSearchLocked()) {
        google.maps.event.trigger(that, 'searchChanged', this.getPlace());
      }
    });

    // Register change event to catch user entry without an "enter".
    $input.change(function(changeEvent) {
      if (!that.isSearchLocked()) {
        var searchText = $(this).val();
        // Create a fake place similar to autocomplete.
        var place = {'name': searchText};
        google.maps.event.trigger(that, 'searchChanged', place);
      }
    });
  };

  /**
   * Drupal.GSL.Panel.prototype.lockSearch
   */
  Drupal.GSL.Panel.prototype.lockSearch = function() {
    this._searchIsLocked = true;
    return this;
  };

  /**
   * Drupal.GSL.Panel.prototype.releaseSearchLock
   */
  Drupal.GSL.Panel.prototype.releaseSearchLock = function() {
    this._searchIsLocked = false;
    return this;
  };

  /**
   * Drupal.GSL.Panel.prototype.isSearchLocked
   */
  Drupal.GSL.Panel.prototype.isSearchLocked = function() {
    return this._searchIsLocked;
  };

  /**
   * Drupal.GSL.Panel.prototype.searchChanged
   */
  Drupal.GSL.Panel.prototype.searchChanged = function(place, zoomRequest) {
    this.lockSearch();

    var view = this.get('view');
    var map = view.getMap();
    var marker = this.getSearchMarker();
    marker.setVisible(false);

    var location = null;
    var locationIsMapCenter = false;

    if (place.geometry) {
      // Place selected.
      location = place.geometry.location;
    }
    else if (place.name) {
      // Query for location of search text.
      this.searchPosition(place.name);

      // Return and leave any locks enabled.
      return;
    }
    else if (!place.name) {
      // Empty input - set location to map center.
      location = map.getCenter();
      locationIsMapCenter = true;
    }

    // Exit if no center.
    if (!location) {
      this.releaseSearchLock();
      return;
    }

    // Map update.
    view.highlight(null);
    var mapZoom = isFinite(zoomRequest) ? zoomRequest : this.getSearchZoomLevel();
    if (!isFinite(mapZoom)) {
      mapZoom = 10;
    }

    map.setCenter(location);
    if (!locationIsMapCenter) {
      map.setZoom(mapZoom);
    }

    // Marker update.
    if (marker) {
      if (place.formatted_address && place.formatted_address.length) {
        marker.setTitle(place.formatted_address);
      }
      else {
        marker.setTitle(location.toString());
      }

      if (!locationIsMapCenter) {
        marker.setPosition(location);
        marker.setVisible(true);
      }
      else {
        marker.setPosition(null);
      }
    }

    // Directions update.
    this.directionsFrom_ = location;
    if (this.directionsVisible_) {
      this.renderDirections_();
    }

    // Listen for store changes in the view.
    // Note: in base class this was called after the view.refreshView().
    this.listenForStoresUpdate_();

    // Update store data feed for the view.
    view.refreshView(location);

    // Release any lock.
    this.releaseSearchLock();
  };

  /**
   * Override listenForStoresUpdate_().
   *
   * Triggers an update for the store list in the Panel. Will wait for stores
   * to load asynchronously from the data source.
   * @private
   */
  Drupal.GSL.Panel.prototype.listenForStoresUpdate_ = function() {
      var that = this;
      var view = this.get('view');
      if (this.storesChangedListener_) {
        google.maps.event.removeListener(this.storesChangedListener_);
      }
      this.storesChangedListener_ = google.maps.event.addListenerOnce(view,
          'stores_changed', function() {
            that.set('stores', view.get('stores'));
          });
  };

  /**
   * Override searchPosition().
   * Search for the specified address.
   * NO pan and zoom.
   * @param {string} searchText the address to pan to.
   */
  Drupal.GSL.Panel.prototype.searchPosition = function(searchText) {
    var that = this;

    if (searchText && searchText.length) {
      var request = {
        address: searchText,
        bounds: this.get('view').getMap().getBounds()
      };

      Drupal.GSL.geocoder.geocode(request, function(result, status) {
        if (status == google.maps.GeocoderStatus.OK) {
          // Trigger searchChanged.
          google.maps.event.trigger(that, 'searchChanged', result[0]);
        }
        else {
          // TODO: proper error handling.
        }
      });
    }
  };

  /**
   * Get search marker.
   * Uses existing or creates a new one if configured to show marker.
   */
  Drupal.GSL.Panel.prototype.getSearchMarker = function() {
    if (!this.searchMarker || !(this.searchMarker instanceof google.maps.Marker)) {
      this.searchMarker = null;
      var showMarker = Drupal.settings.gsl && Drupal.settings.gsl.display_search_marker;
      if (showMarker && this.get('view')) {
        // Initialize marker.
        var markerOptions = {
          title: 'You are here',
          // Use Google's default blue marker.
          icon: '//maps.google.com/mapfiles/ms/icons/blue-dot.png',
          map: this.get('view').getMap()
        };

        this.searchMarker = new google.maps.Marker(markerOptions);
      }
    }

    return this.searchMarker;
  };

  /**
   * Override renderDirections_().
   * This is needed to override "geocode" listener.
   */
  Drupal.GSL.Panel.prototype.renderDirections_ = function() {
    var that = this;

    if (!this.directionsTo_) {
      return;
    }

    // Clear out existing directions.
    var rendered = this.directionsPanel_.find('.rendered-directions').empty();

    // Use search marker instead of directionsFrom_.
    // this.directionsFrom_
    var searchMarker = this.getSearchMarker();
    if (!searchMarker || !searchMarker.getPosition()) {
      return;
    }

    this.directionsFrom_ = searchMarker.getPosition();

    this.directionsService_.route({
      origin: this.directionsFrom_,
      destination: this.directionsTo_.getLocation(),
      travelMode: google.maps['DirectionsTravelMode'].DRIVING
    }, function(result, status) {
      if (status != google.maps.DirectionsStatus.OK) {
        return;
      }

      var renderer = that.directionsRenderer_;
      renderer.setPanel(rendered[0]);
      renderer.setMap(that.get('view').getMap());
      renderer.setDirections(result);
    });
  };

  /**
   * Override hideDirections()
   * Hides the directions panel.
   */
  Drupal.GSL.Panel.prototype.hideDirections = function() {
    this.directionsVisible_ = false;
    this.directionsPanel_.fadeOut();
    this.featureFilter_.fadeIn();
    this.storeList_.fadeIn();
    this.directionsRenderer_.setMap(null);
  };

  /**
   * Override showDirections().
   * Shows directions to the selected store.
   */
  Drupal.GSL.Panel.prototype.showDirections = function() {
    var store = this.get('selectedStore');
    this.featureFilter_.fadeOut();
    this.storeList_.fadeOut();
    this.directionsPanel_.find('.directions-to').val(store.getDetails().title);
    this.directionsPanel_.fadeIn();
    this.renderDirections_();

    this.directionsVisible_ = true;
  };

  /**
   * Overridden storeLocator.Panel.prototype.stores_changed.
   *
   * Triggered when the storeLocator.View's stores property changes.
   * See Drupal.GSL.Panel.listenForStoresUpdate_()
   */
  Drupal.GSL.Panel.prototype.stores_changed = function() {
    if (!this.get('stores')) {
      return;
    }

    var view = this.get('view');
    var bounds = view && view.getMap().getBounds();

    var that = this;
    var stores = this.get('stores');
    var selectedStore = this.get('selectedStore');
    this.storeList_.empty();

    if (!stores.length) {
      this.storeList_.append('<li class="no-stores">' + Drupal.t('There are no stores in this area.') + '</li>');
    } else if (bounds && !bounds.contains(stores[0].getLocation())) {
      this.storeList_.append('<li class="no-stores">' + Drupal.t('@msg', {'@msg': Drupal.settings.gsl[Drupal.GSL.currentMap.mapid]['no_results']}) + '</li>');
    }

    var clickHandler = function() {
      view.highlight(this['store'], true);
    };

    // Add stores to list
    var items_per_panel = this.get('items_per_panel');
    // Initialize the map value in order to get proximity
    var map = view.getMap() || Drupal.GSL.currentMap;

    // Set proximity variables.
    var metricText, proximityMultiplier;
    var proximityEnabled = Drupal.settings.gsl.proximity;
    if (proximityEnabled) {
      // Determine if the user wants values converted to MI or KM.
      // As the base value is in KM, apply a multiplier for KM to MI if desired.
      if (Drupal.settings.gsl.metric == 'mi'){
        proximityMultiplier = .621371;
        metricText = 'miles';
      }
      else{
        proximityMultiplier = 1;
        metricText = 'km';
      }
    }

    // Set before stores loop so it can be used for distance calculations.
    // Use home marker if exists and is on a map, else
    var originLatLng = null;
    var searchMarker = this.getSearchMarker();
    if (searchMarker && searchMarker.getPosition()) {
      originLatLng = searchMarker.getPosition();
    }

    // loop through all store values
    for (var i = 0, ii = Math.min(items_per_panel, stores.length); i < ii; i++) {
      // Get store data
      var storeLi = stores[i].getInfoPanelItem();

     // Check if proximity was desired, and if so render it.
      if (proximityEnabled) {
        var $distanceElement = $('.distance', storeLi);

        if (originLatLng) {
          // Calculate distance to the store
          var storeDistance = Number((stores[i].distanceTo(originLatLng) * proximityMultiplier).toFixed(2));

          // add distance to HTML
          if ($distanceElement.length > 0) {
            //if distance field already there, change text.
            $distanceElement.text(storeDistance + ' miles');
          }
          else {
            // No distance field yet! APPEND full HTML!
            $('.address', storeLi).append('<div class="distance">' + storeDistance + ' ' + metricText + '</div>');
          }
        }
        else if ($distanceElement.length > 0) {
          $distanceElement.text('');
        }
      }

      storeLi['store'] = stores[i];
      if (selectedStore && stores[i].getId() == selectedStore.getId()) {
        $(storeLi).addClass('highlighted');
      }

      if (!storeLi.clickHandler_) {
        storeLi.clickHandler_ = google.maps.event.addDomListener(
          storeLi, 'click', clickHandler);
      }

      that.storeList_.append(storeLi);
    }
  };

  /**
   * Overridden storeLocator.Panel.prototype.selectedStore_changed
   */
  Drupal.GSL.Panel.prototype.selectedStore_changed = function() {
    // Call the parent method in the context of this object using 'this'.
    this.parent.prototype.selectedStore_changed.apply(this, arguments);

    // Remember that this method runs on the initial map build. Then it runs
    // again when you select a store in the panel. We only care about the latter
    // event for disabling the Street View link.

    // We use store to determine if it's the initial map build or the 'select a
    // store' in the panel event. We only care about the event.
    var store = this.get('selectedStore');
    if (store) {
      this.directionsTo_ = store;

      // At this point all the links are added to the selected store. We should
      // first check that the Street View imagery exists: if no then disable the
      // link.

      // Create a StreetViewService object that we use to check if the Street
      // View imagery associated with the selected store is available.
      var sv = new google.maps.StreetViewService();
      // We're gonna limit the search for imagery to 50 meters.
      sv.getPanoramaByLocation(store.getLocation(),  50, function(data, status) {
        if (status != google.maps.StreetViewStatus.OK) {

          $("a[class='action streetview']").after($('<span>').attr({
            'class': 'action streetview',
            'style': 'color:#C9C9C9'
          }).html($("a[class='action streetview']").text()));

          $("a[class='action streetview']").remove();
        }
      });
    }
  };

  /**
   * Overridden storeLocator.Panel.prototype.view_changed.
   */
  Drupal.GSL.Panel.prototype.view_changed = function() {
    var that = this;
    this.parent.prototype.view_changed.apply(this, arguments);

    var view = this.get('view');
    var map = view.getMap();

    // Remove zoom listener to fix bug that causes the map to center on the
    // selected store after zooming.
    google.maps.event.clearListeners(map, 'zoom_changed');
    this.zoomListener_ = google.maps.event.addListener(map, 'zoom_changed', function() {
      if (!that.isSearchLocked()) {
        that.stores_changed();
      }
    });

    // Remove geocodelocation listener since this is implemented in GSL
    // location aware.
    google.maps.event.clearListeners(view, 'load');

    // Re-bind autocomplete handler.
    if (this.autoCompleteHandler) {
      this.autoCompleteHandler.bindTo('bounds', map);
    }
  };

  /**
   * Returns the data feed object.
   *
   * New method for storeLocator.View.
   */
  storeLocator.View.prototype.getDataFeed = function() {
    return this.data_ || null;
  }

  /**
   * Override refreshView().
   *
   * Refresh the map's view. This will fetch new data based on the map's bounds.
   * Note: Overriding actual base class and not extending to a new class.
   *
   * @param LatLng centerPoint
   *   Optional. Set to force the stores to be sorted by distance from this
   *   point instead of the map.getBounds().getCenter() that the base
   *   classes implemented.
   */
  storeLocator.View.prototype.refreshView = function(centerPoint) {
    var that = this;

    // TODO: should this use panel.searchMarker || map center || null?
    if (!centerPoint || typeof centerPoint == 'undefined') {
      centerPoint = null;
      if (this.getMap()) {
        centerPoint = this.getMap().getCenter();
      }
    }

    var dataFeed = this.getDataFeed();
    if (dataFeed) {
      dataFeed.getStores(
        this.getMap().getBounds(),
        this.get('featureFilter'),
        function(stores) {
          var oldStores = that.get('stores');
          if (oldStores) {
            for (var i = 0, ii = oldStores.length; i < ii; i++) {
              google.maps.event.removeListener(
                  oldStores[i].getMarker().clickListener_);
            }
          }
          that.set('stores', stores);
        },
        centerPoint
      );
    }
  };

  /**
   * Override addStoreToMap() to implement marker cluster.
   *
   * Note: Overriding actual base class and not extending to a new class.
   *
   * Add a store to the map.
   * @param {storeLocator.Store} store the store to add.
   */
  storeLocator.View.prototype.addStoreToMap = function(store) {
    var marker = this.getMarker(store);
    store.setMarker(marker);
    var that = this;

    marker.clickListener_ = google.maps.event.addListener(marker, 'click',
      function() {
        that.highlight(store, false);
      });

    if (marker.getMap() != this.getMap()) {
      // Marker hasn't been added to the map before. Decide what to do with it.
      var markerClusterEnabled = Drupal.settings.gsl[Drupal.GSL.currentMap.mapid]['mapcluster'];
      var markerClusterZoom = Drupal.settings.gsl[Drupal.GSL.currentMap.mapid]['mapclusterzoom'];
      var switchToMarkerCluster = (Drupal.GSL.currentMap.getZoom() < markerClusterZoom);
      if (markerClusterEnabled && switchToMarkerCluster) {
        // Marker is added to the cluster.
        Drupal.GSL.currentCluster.addMarker(marker);
      }
      else {
        // Marker is added directly to the map.
        marker.setMap(this.getMap());
      }
    }
  };

  /**
   * Create the marker cluster.
   */
  Drupal.GSL.initializeCluster = function (stores, that) {
    var map = Drupal.GSL.currentMap;
    var markerClusterZoom = Drupal.settings.gsl[Drupal.GSL.currentMap.mapid]['mapclusterzoom'];
    var markerClusterGrid = Drupal.settings.gsl[Drupal.GSL.currentMap.mapid]['mapclustergrid'];
    var mcOptions = {gridSize: markerClusterGrid, maxZoom: Drupal.settings.gsl.max_zoom};
    // We populate it later in addStoreToMap().
    Drupal.GSL.currentCluster = new MarkerClusterer(map, [], mcOptions);
  };

  /**
   * Create map on window load
   */
  Drupal.behaviors.googleStoreLocator = {
    attach: function (context, context_settings) {

      // Process all maps on the page.
      var locators = [];
      for (var mapid in Drupal.settings.gsl) {
        if (!(mapid in Drupal.settings.gsl)) {
          continue;
        }

        var $container = $('#' + mapid, context).once('gsl-init');
        if (!$container.length) {
          continue;
        }

        var $canvas = $('.google-store-locator-map', $container);
        if (!$canvas.length) {
          continue;
        }

        var $panel = $('.google-store-locator-panel', $container);
        if (!$panel.length) {
          continue;
        }

        var map_settings = Drupal.settings.gsl[mapid];
        var locator = {};

        // Get data
        locator.data = new Drupal.GSL.dataSource(map_settings['datapath']);

        locator.elements = {
          canvas: $canvas.get(0),
          panel: $panel.get(0)
        };

        locator.map = new google.maps.Map(locator.elements.canvas, {
          // Default center on North America.
          center: new google.maps.LatLng(map_settings['maplat'], map_settings['maplong']),
          zoom: map_settings['mapzoom'],
          maxZoom: Drupal.settings.gsl.max_zoom,
          mapTypeId: map_settings['maptype'] || google.maps.MapTypeId.ROADMAP,
          styles: map_settings['map_style']
        });

        Drupal.GSL.setCurrentMap(locator.map, mapid);

        var feature_list = map_settings['feature_list'];
        var storeFeatureSet = new storeLocator.FeatureSet;
        // Loop through the feature list and add each from the admin provided allowed values.
        for(var feature in feature_list) {
          // Mimic the id creation we did when parsing the stores.
          var id = feature_list[feature].replace(/\s/g,'');
          var storeFeature = new storeLocator.Feature(id, feature_list[feature]);
          storeFeatureSet.add(storeFeature);
        }

        // Create view.
        locator.view = new storeLocator.View(locator.map, locator.data, {
          markerIcon: map_settings['marker_url'],
          geolocation: false,
          features: storeFeatureSet
        });

        // Set reference to data feed after view is initialized.
        // This is needed in the overridden
        // storeLocator.View.prototype.refreshView().
        locator.view.set('data_', locator.data);

        // Create panel.
        locator.panel = new Drupal.GSL.Panel(locator.elements.panel, {
          view: locator.view,
          items_per_panel: map_settings['items_per_panel'],
          locationSearch: true,
          locationSearchLabel: map_settings['search_label'],
          featureFilter: true,
          mapSettings: map_settings
        });

        locators.push(locator);
      } // mapid loop

      // Trigger gslReady event for all locators.
      var gslReadyEvent = jQuery.Event('gslReady');
      gslReadyEvent.gslLocators = locators;
      $(document).trigger(gslReadyEvent);

      // Cleanup.
      locator = null;
      locators = null;
      gslReadyEvent = null;
    } // /attach
  };

})(jQuery, Drupal, this, this.document);
