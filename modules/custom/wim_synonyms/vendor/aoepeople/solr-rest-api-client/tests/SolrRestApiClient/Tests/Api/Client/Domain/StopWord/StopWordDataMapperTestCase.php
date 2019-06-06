<?php

namespace SolrRestApiClient\Tests\Api\Client\Domain\StopWord;

use SolrRestApiClient\Api\Client\Domain\StopWord\StopWord;
use SolrRestApiClient\Api\Client\Domain\StopWord\StopWordCollection;
use SolrRestApiClient\Api\Client\Domain\StopWord\StopWordDataMapper;
use SolrRestApiClient\Tests\BaseTestCase;

class StopWordDataMapperTestCase extends BaseTestCase {

	/**
	 * @var StopWordDataMapper
	 */
	protected $dataMapper = null;

	/**
	 * @return void
	 */
	public function setUp() {
		$this->dataMapper = new StopWordDataMapper();
	}

	/**
	 * @test
	 */
	public function canBuildJsonFromStopWordCollection() {
		$stopWordCollection = new StopWordCollection();

		$stopWord = new StopWord();
		$stopWord->setWord("test");
		$stopWordCollection->add($stopWord);

		$this->assertEquals(1, $stopWordCollection->getCount());
		$expectedJson = '["test"]';
		$json = $this->dataMapper->toJson($stopWordCollection);

		$this->assertEquals($expectedJson, $json);
	}

	/**
	 * @test
	 */
	public function canBuildStopWordCollectionFromJson() {
		$input = '{
					  "responseHeader": {
						"status": 0,
						"QTime": 3
					  },
					  "wordSet": {
						"initArgs": {
						  "ignoreCase": false
						},
						"initializedOn": "2014-05-19T13:11:24.567Z",
						"updatedSinceInit": "2014-05-19T13:12:12.415Z",
						"managedList": [
						  "one",
						  "two"
						]
					  }
				}';

		$stopWordCollection = $this->dataMapper->fromJson($input);
		$this->assertEquals(2, $stopWordCollection->getCount(), 'Unexpected amount of stopWords after reconstitution.');

		/** @var $first StopWord */
		$first = $stopWordCollection->getByIndex(0);
		$this->assertEquals("one", $first->getWord(), 'Could not create solr stopWord collection from rest api response');
	}
}