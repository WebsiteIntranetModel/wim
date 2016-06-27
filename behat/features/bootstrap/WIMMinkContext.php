<?php

/**
 * This file contains function for Mink
 *
 * PHP version 5.6
 *
 * @category MinkContext
 * @package  Behat
 * @author   Display Name <username@example.com>
 * @license  http://www.gnu.org/copyleft/gpl.html GNU General Public License
 * @link     none
 */

use Drupal\DrupalExtension\Context\MinkContext;

/**
 * Defines application features from the specific context.
 *
 * @category WIMMinkContext
 * @package  Behat
 * @author   Display Name <username@example.com>
 * @author   Display Name <username@example.com>
 * @license  http://www.gnu.org/copyleft/gpl.html GNU General Public License
 * @link     none
 */
class WIMMinkContext extends MinkContext
{
    /**
     * Makes the step case insensitive.
     *
     * @param string $heading heading
     * @param string $region  region
     *
     * @override MinkContext::assertRegionHeading()
     * @throws   \Exception
     * @return   void
     */
    public function assertRegionHeading($heading, $region)
    {
        $regionObj = $this->getRegion($region);
        $heading = strtolower($heading);

        foreach (array('h1', 'h2', 'h3', 'h4', 'h5', 'h6') as $tag) {
            $elements = $regionObj->findAll('css', $tag);
            if (!empty($elements)) {
                foreach ($elements as $element) {
                    if (trim(strtolower($element->getText())) === $heading) {
                        return;
                    }
                }
            }
        }

        $message = sprintf(
            'The heading "%s" was not found in the "%s" region on the page %s',
            $heading,
            $region,
            $this->getSession()->getCurrentUrl()
        );
        throw new \Exception($message);
    }
}
