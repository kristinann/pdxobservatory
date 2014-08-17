{
  "type" : "FeatureCollection",
  "features" : [
    <?php
      $geoms = array ( );
      foreach ( $geojson as $feat ) {
        $geom  = '{';
        $geom .= '"type": "Feature",';
        $geom .= '"geometry": ' . $feat->geojson . ',';
        unset ( $feat->geojson );
        $geom .= '"properties": ' . json_encode ( $feat, JSON_NUMERIC_CHECK );
        $geom .= '}';

        $geoms[] = $geom;
      }

      echo implode ( ',', $geoms );
    ?>
  ]
}