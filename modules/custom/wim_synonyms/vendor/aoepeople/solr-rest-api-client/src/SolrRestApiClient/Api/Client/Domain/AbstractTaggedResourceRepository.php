<?php

namespace SolrRestApiClient\Api\Client\Domain;

use SolrRestApiClient\Api\Client\Domain\ManagedResource\TaggedResource;

/**
 * Class AbstractTaggedResourceRepository
 *
 * @author Timo Schmidt <timo.schmidt@aoe.com>
 * @package SolrRestApiClient\Api\Client\Domain
 */
abstract class AbstractTaggedResourceRepository extends AbstractRepository {

	/**
	 * @var TaggedResource
	 */
	protected $taggedResource;

	/**
	 * @return TaggedResource
	 */
	public function getResource() {
		return $this->taggedResource;
	}

	/**
	 * @param TaggedResource $taggedResource
	 */
	public function setResource(TaggedResource $taggedResource) {
		$this->taggedResource = $taggedResource;
	}

	/**
	 * @param null $forcedTag
	 * @return string
	 */
	protected function getTag($forcedTag = null) {
		if($forcedTag !== null) {
			return $forcedTag;
		} elseif ($this->taggedResource instanceof TaggedResource && trim($this->taggedResource->getTag()) != "") {
			return $this->taggedResource->getTag();
		} else {
			return "default";
		}
	}
}