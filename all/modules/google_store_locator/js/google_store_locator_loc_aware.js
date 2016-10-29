(function ($, Drupal, window, document, undefined) {
  Drupal.GSL = Drupal.GSL || {};

  // React to the gslReady event.
  $(document).bind('gslReady', function(event) {
    // Exit if cannot process.
    if (!event.gslLocators || !event.gslLocators.length || !window.navigator || !window.navigator.geolocation) {
      return;
    }

    var gslLocators = event.gslLocators;

    /**
     * Success callback if we're able to obtain lat/lng coordinates for a user.
     */
    function positionSuccess(position) {
      if (gslLocators.length) {
        var gslLocatorsLocal = gslLocators;

        // Centre the map on the new location
        var latLng = new google.maps.LatLng(position.coords.latitude, position.coords.longitude);

        // Reverse geocode.
        Drupal.GSL.geocoder.geocode({'location': latLng}, function(results, status) {
          if (status == google.maps.GeocoderStatus.OK && results && results.length) {
            var place = results[0];
            for (var i = 0; i < gslLocatorsLocal.length; i++) {
              var locator = gslLocatorsLocal[i];
              if (locator.panel && locator.panel.locationSearchElement) {
                var $searchBox = $('input', locator.panel.locationSearchElement);
                if ($searchBox.length && !$searchBox.val()) {
                  $searchBox.val(place.formatted_address);
                  google.maps.event.trigger(locator.panel, 'searchChanged', place, locator.panel.getMapSetting('loc_aware_zoom'));
                }
              }
            }
          }
        });
      }
    }

    /**
     * Error callback if for some reason we can't get the users location.
     */
    function positionError(err) {
      var msg;
      switch(err.code) {
        case err.PERMISSION_DENIED:
          msg = "Permission denied in finding your location";
          break;
        case err.POSITION_UNAVAILABLE:
          msg = "Your location is currently unknown";
          break;
        case err.TIMEOUT:
        case err.BREAK:
          msg = "Attempt to find location has timed out.";
          break;
        case err.UNKNOWN_ERROR:
          msg = "Unable to find your location";
          break;
        default:
          msg = "Location detection not supported in browser";
      }

      // Does this element even exist?
      document.getElementById('info').innerHTML = msg;
    }

    // Get the user's current position.
    window.navigator.geolocation.getCurrentPosition(positionSuccess, positionError, ({
      maximumAge: 60 * 1000,
      timeout: 10 * 1000
    }));
  });
})(jQuery, Drupal, this, this.document);
