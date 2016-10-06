<?php
/**
 * @file
 * Template for Read Speaker.
 *
 * Available variables:
 * - $title: URL title.
 * - $customer_id: Customer id.
 * - $lang: Language code.
 * - $url: Current page URL.
 * - $button: Listen button text.
 */
?>
<div id="readspeaker-button" class="rs_skip rsbtn rs_preserve">
  <a class="rsbtn_play" title="<?php print $title; ?>"
     href="//app.readspeaker.com/cgi-bin/rsent?customerid=<?php print $customer_id; ?>&amp;lang=<?php print $lang; ?>&amp;readid=main&amp;url=<?php print $url; ?>">
    <span class="rsbtn_left rsimg rspart"><span
        class="rsbtn_text"><span><?php print $button; ?></span></span></span>
    <span class="rsbtn_right rsimg rsplay rspart"></span>
  </a>
</div>
