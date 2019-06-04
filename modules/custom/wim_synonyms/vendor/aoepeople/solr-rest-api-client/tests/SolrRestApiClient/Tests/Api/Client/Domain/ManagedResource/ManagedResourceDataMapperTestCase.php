<?php

namespace SolrRestApiClient\Tests\Api\Client\Domain\Synonym;

use SolrRestApiClient\Api\Client\Domain\ManagedResource\ManagedResourceDataMapper;
use SolrRestApiClient\Tests\BaseTestCase;

class ManagedResourceDataMapperTestCase extends BaseTestCase {

	/**
	 * @var ManagedResourceDataMapper
	 */
	protected $dataMapper;

	/**
	 * @return void
	 */
	public function setUp() {
		$this->dataMapper = new ManagedResourceDataMapper();
	}

	/**
	 * @test
	 */
	public function canGetSynonymResources() {
		$fixtureResponse    = $this->getFixtureContent('/Api/Client/Domain/ManagedResource/Fixtures/managedResponse.json');
		$resourceCollection = $this->dataMapper->fromJson($fixtureResponse);

		$this->assertEquals(2, $resourceCollection->getCount(), 'Unexpected number of resources returned by the api');
		$this->assertEquals(1, $resourceCollection->getSynonymResources()->getCount(),'Unexpected number of synonym resources');
		$this->assertEquals(1, $resourceCollection->getStopWordResources()->getCount(),'Unexpected number of stop word resources');

	}

}