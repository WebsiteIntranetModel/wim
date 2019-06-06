<?php

namespace SolrRestApiClient\Api\Client\Domain\ManagedResource;

use SolrRestApiClient\Api\Client\Domain\JsonDataMapperInterface;
use SolrRestApiClient\Api\Client\Domain\StopWord\StopWord;

/**
 * Class ManagedResourcesDataMapper
 */
class ManagedResourceDataMapper implements JsonDataMapperInterface {

	/**
	 * @param string $json
	 * @return ManagedResourceCollection
	 */
	public function fromJson($json) {
		$resourceCollection = new ManagedResourceCollection();

		$object = json_decode($json);

		if (!is_object($object) || !isset($object->managedResources) || count($object->managedResources) == 0) {
			return $resourceCollection;
		}

		foreach ($object->managedResources as $resources) {
			if (preg_match('/synonyms/', $resources->resourceId)) {
				$matches = preg_split('/synonyms\\//', $resources->resourceId);

				$synonymResource = new SynonymResource();
				$synonymResource->setTag($matches[1]);

				$resourceCollection->add($synonymResource);
			}

			if (preg_match('/stopwords/', $resources->resourceId)) {
				$matches = preg_split('/stopwords\\//', $resources->resourceId);

				$stopWordResource = new StopWordResource();
				$stopWordResource->setTag($matches[1]);

				$resourceCollection->add($stopWordResource);
			}

		}
		return $resourceCollection;
	}

	/**
	 * @param $object
	 * @return string
	 */
	public function toJson($object) {
		// TODO: Implement toJson() method.
	}
}