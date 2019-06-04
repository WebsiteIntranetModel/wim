<?php

namespace SolrRestApiClient\Api\Client\Domain\ManagedResource;

use SolrRestApiClient\Api\Client\Domain\AbstractRepository;

/**
 * Repository to manage resources in solr using the RestAPI
 *
 * @author Nikolay Diaur <nikolay.diaur@aoe.com>
 */
class ManagedResourceRepository extends AbstractRepository {

	/**
	 * @var string
	 */
	protected $restEndPointPath = 'schema/managed';

	/**
	 * @param ManagedResourceDataMapper $dataMapper
	 */
	public function injectDataMapper(ManagedResourceDataMapper $dataMapper) {
		$this->dataMapper = $dataMapper;
	}

	/**
	 * @return ManagedResourceCollection
	 */
	public function getAll() {
		$endpoint   = $this->getEndpoint();
		$response   = $this->executeGetRequest($endpoint);
		$result     = $response->getBody(true);

		return $this->dataMapper->fromJson($result);
	}
}