<?php

/**
 * @file
 * This file contains function for Mink.
 */

use Drupal\DrupalExtension\Context\MinkContext;

/**
 * Defines application features from the specific context.
 */
class WIMMinkContext extends MinkContext {

  /**
   * Makes the step case insensitive.
   *
   * @override MinkContext::assertRegionHeading()
   */
  public function assertRegionHeading($heading, $region) {
    $regionObj = $this->getRegion($region);

    foreach (array('h1', 'h2', 'h3', 'h4', 'h5', 'h6') as $tag) {
      $elements = $regionObj->findAll('css', $tag);
      if (!empty($elements)) {
        foreach ($elements as $element) {
          if (trim(strtolower($element->getText())) === strtolower($heading)) {
            return;
          }
        }
      }
    }

    throw new \Exception(sprintf('The heading "%s" was not found in the "%s" region on the page %s', $heading, $region, $this->getSession()->getCurrentUrl()));
  }

}
