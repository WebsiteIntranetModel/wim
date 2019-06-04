<?php

namespace SolrRestApiClient\Tests\Api\Client\Domain\Synonym;

use SolrRestApiClient\Api\Client\Domain\Synonym\Synonym;
use SolrRestApiClient\Api\Client\Domain\Synonym\SynonymCollection;
use SolrRestApiClient\Api\Client\Domain\Synonym\SynonymDataMapper;
use SolrRestApiClient\Api\Client\Domain\Synonym\SynonymRepository;
use SolrRestApiClient\Tests\BaseTestCase;

class SynonymRepositoryTestCase extends BaseTestCase {

	/**
	 * @var SynonymDataMapper
	 */
	protected $dataMapper = null;

	/**
	 * @var \SolrRestApiClient\Api\Client\Domain\Synonym\SynonymRepository()
	 */
	protected $synonymRepository;

	/**
	 * @return void
	 */
	public function setUp() {
		$this->dataMapper = new SynonymDataMapper();
		$this->synonymRepository = $this->getMock('SolrRestApiClient\Api\Client\Domain\Synonym\SynonymRepository',array('executeDeleteRequest','executeGetRequest','executePostRequest'));
		$this->synonymRepository->injectDataMapper($this->dataMapper);
	}

	/**
	 * @return void
	 */
	public function tearDown() {}

	/**
	 * @test
	 */
	public function canAddAll() {
		$synonymCollection = new \SolrRestApiClient\Api\Client\Domain\Synonym\SynonymCollection();
		$synonym = new \SolrRestApiClient\Api\Client\Domain\Synonym\Synonym();
		$synonym->setMainWord('foo');
		$synonym->addWordsWithSameMeaning('bar');
		$synonym->addWordsWithSameMeaning('bla');
		$synonym->addWordsWithSameMeaning('bluqqqqqqqqqqq');

		$synonymCollection->add($synonym);

		$expectedJson = '{"foo":["bar","bla","bluqqqqqqqqqqq"]}';
		$responseMock = $this->getMock('Guzzle\Http\Message\Response',array('getBody','getStatusCode'), array(),'',false);
		$responseMock->expects($this->once())->method('getStatusCode')->will($this->returnValue(200));
		$this->synonymRepository->expects($this->once())->method('executePostRequest')->with('solr/schema/analysis/synonyms/it',$expectedJson)->will(
			$this->returnValue($responseMock)
		);

		$result = $this->synonymRepository->addAll($synonymCollection, 'it');
		$this->assertTrue($result);
	}

	/**
	 * @test
	 */
	public function canGetAllSynonyms() {
		$responseMock = $this->getMock('Guzzle\Http\Message\Response',array('getBody'), array(),'',false);

		$fixtureResponse = '{
 		    "responseHeader": {
                "status": 0,
                "QTime": 3
              },
             "synonymMappings": {
                "initArgs": {
                    "ignoreCase": false
                },
	            "initializedOn": "2014-05-19T15:32:37.988Z",
                 "managedMap": {
                    "foo": [
                        "bar",
                     "bla"
                    ],
	                "sad": [
                        "unhappy"
                    ],
                    "sada": [
                        "unhappy",
                        "unhapy"
                    ]
                }
              }
			}';

		$responseMock->expects($this->once())->method('getBody')->will($this->returnValue(
			$fixtureResponse
		));
		$this->synonymRepository->expects($this->once())->method('executeGetRequest')->with('solr/schema/analysis/synonyms/it')->will(
			$this->returnValue($responseMock)
		);

		$synonymsAll = $this->synonymRepository->getAll("it");
		$this->assertInstanceOf('SolrRestApiClient\Api\Client\Domain\Synonym\SynonymCollection', $synonymsAll);
		$this->assertEquals(3,$synonymsAll->getCount(),'Unexpected amount of synonyms retrieved');
	}

	/**
	 * @test
	 */
	public function canGetByMainWord() {
		$fixtureResponse = '{
		    "responseHeader": {
                "status": 0,
                "QTime": 6
            },
            "sada": [
                "bar",
                "bla",
                "whatever"
            ]
		}';

		$responseMock = $this->getMock('Guzzle\Http\Message\Response',array('getBody'), array(),'',false);
		$responseMock->expects($this->once())->method('getBody')->will($this->returnValue(
			$fixtureResponse
		));

		$this->synonymRepository->expects($this->once())->method('executeGetRequest')->will(
			$this->returnValue($responseMock)
		);

		$synonyms2 = $this->synonymRepository->getByMainWord("sada","it");
		$this->assertEquals(3, count($synonyms2->getByIndex(0)->getWordsWithSameMeaning()), "Amount of retrieved words with same meaning not equal to added");

		$wordsWithSameMeaning = array_values($synonyms2->getByIndex(0)->getWordsWithSameMeaning());
		$this->assertEquals("whatever", $wordsWithSameMeaning[2], "Amount of retrieved words with same meaning not equal to added");
		$this->assertEquals("sada", $synonyms2->getByIndex(0)->getMainWord(), "Main word not equal to added main word");
	}

	/**
	 * @test
	 */
	public function canDeleteByMainWord() {
		$responseMock = $this->getMock('Guzzle\Http\Message\Response',array('getBody'), array(),'',false);
		$this->synonymRepository->expects($this->once())->method('executeDeleteRequest')->with('solr/schema/analysis/synonyms/it/test')->will(
			$this->returnValue($responseMock)
		);
		$this->synonymRepository->deleteByMainWord('test',"it");
	}

	/**
	 * @test
	 */
	public function canDeleteAll() {
		$synonymsCount = 5;
		$synonymCollection = new \SolrRestApiClient\Api\Client\Domain\Synonym\SynonymCollection();

		for($i = 0; $i < $synonymsCount; $i++) {
			$synonym = new \SolrRestApiClient\Api\Client\Domain\Synonym\Synonym();
			$synonym->setMainWord('foo');
			$synonym->addWordsWithSameMeaning('bar');
			$synonym->addWordsWithSameMeaning('bla');
			$synonym->addWordsWithSameMeaning('bluqqqqqqqqqqq');

			$synonymCollection->add($synonym);
		}

		$this->synonymRepository = $this->getMock('SolrRestApiClient\Api\Client\Domain\Synonym\SynonymRepository',array('executeDeleteRequest','executeGetRequest','executePostRequest', 'getAll', 'getTag'));
		$this->synonymRepository->injectDataMapper($this->dataMapper);

		$this->synonymRepository->expects($this->once())->method('getTag');
		$this->synonymRepository->expects($this->once())->method('getAll')->will($this->returnValue(
			$synonymCollection
		));

		$responseMock = $this->getMock('Guzzle\Http\Message\Response',array('getBody','getStatusCode'), array(),'',false);
		$responseMock->expects($this->exactly($synonymsCount))->method('getStatusCode')->will($this->returnValue(200));

		$endpoint = 'solr/schema/analysis/synonyms//foo';
		$this->synonymRepository->expects($this->exactly($synonymsCount))->method('executeDeleteRequest')->with($endpoint)->will($this->returnValue(
			$responseMock
		));

		$this->assertTrue($this->synonymRepository->deleteAll());
	}

}