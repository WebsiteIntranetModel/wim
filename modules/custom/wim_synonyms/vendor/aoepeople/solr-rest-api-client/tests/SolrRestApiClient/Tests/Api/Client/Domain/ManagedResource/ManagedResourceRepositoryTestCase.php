<?php

namespace SolrRestApiClient\Tests\Api\Client\Domain\Synonym;

use SolrRestApiClient\Api\Client\Domain\ManagedResource\ManagedResourceRepository;
use SolrRestApiClient\Api\Client\Domain\ManagedResource\ManagedResourceDataMapper;
use SolrRestApiClient\Api\Client\Domain\ManagedResource\ManagedResourceCollection;
use SolrRestApiClient\Tests\BaseTestCase;

/**
 * Class ManagedResourceRepositoryTestCase
 * @package SolrRestApiClient\Tests\Api\Client\Domain\Synonym
 */
class ManagedResourceRepositoryTestCase extends BaseTestCase {

	/**
	 * @test
	 */
	public function canGetSynonymResources() {
		$responseMock = $this->getMock('Guzzle\Http\Message\Response',array('getBody'), array(),'',false);

		$fixtureResponse = '
			{
			  "responseHeader":{
			    "status":0,
			    "QTime":3
			  },
			  "managedResources":[
			    {
			      "resourceId":"/schema/analysis/stopwords/english",
			      "class":"org.apache.solr.rest.schema.analysis.ManagedWordSetResource",
			      "numObservers":"1"
			    },
			    {
			      "resourceId":"/schema/analysis/synonyms/english",
			      "class":"org.apache.solr.rest.schema.analysis.ManagedSynonymFilterFactory$SynonymManager",
			      "numObservers":"1"
			    },
			    {
			      "resourceId":"/schema/analysis/synonyms/deutsch",
			      "class":"org.apache.solr.rest.schema.analysis.ManagedSynonymFilterFactory$SynonymManager",
			      "numObservers":"1"
			    }
			  ]
			}';
		$responseMock->expects($this->once())->method('getBody')->will($this->returnValue(
			$fixtureResponse
		));

		$dataMapper = new ManagedResourceDataMapper();
		$mockedManagedResourceRepository = $this->getAccessibleMock('SolrRestApiClient\Api\Client\Domain\ManagedResource\ManagedResourceRepository', array('executeGetRequest', 'getEndpoint'));
		$mockedManagedResourceRepository->injectDataMapper($dataMapper);
		$mockedManagedResourceRepository->expects($this->once())->method('executeGetRequest')->will(
			$this->returnValue($responseMock)
		);

		/**
		 * @var $managedResponse ManagedResourceCollection
		 */
		$managedResponse = $mockedManagedResourceRepository->getAll();
		$this->assertInstanceOf('SolrRestApiClient\Api\Client\Domain\ManagedResource\ManagedResourceCollection', $managedResponse);
		$this->assertEquals(2, $managedResponse->getSynonymResources()->getCount(),'Unexpected amount of managed resources retrieved');
	}
}