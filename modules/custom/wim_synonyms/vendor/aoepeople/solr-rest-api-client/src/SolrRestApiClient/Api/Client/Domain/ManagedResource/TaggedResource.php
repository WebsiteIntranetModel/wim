<?php

namespace SolrRestApiClient\Api\Client\Domain\ManagedResource;

/**
 * Class TaggedResource
 * @package SolrRestApiClient\Api\Client\Domain\ManagedResource
 */
class TaggedResource extends ManagedResource {

	/**
	 * @var string
	 */
	protected $tag = '';

	/**
	 * @return string
	 */
	public function getTag() {
		return $this->tag;
	}

	/**
	 * @param string $tag
	 */
	public function setTag($tag) {
		$this->tag = $tag;
	}
}