<?php
/**
 * Created by IntelliJ IDEA.
 * User: pavelbogomolenko
 * Date: 5/27/14
 * Time: 1:17 PM
 * To change this template use File | Settings | File Templates.
 */

namespace SolrRestApiClient\Tests\Api\Client\Domain\StopWord;

use SolrRestApiClient\Api\Client\Domain\StopWord\StopWord;
use SolrRestApiClient\Api\Client\Domain\StopWord\StopWordCollection;
use SolrRestApiClient\Api\Client\Domain\StopWord\StopWordDataMapper;
use SolrRestApiClient\Api\Client\Domain\StopWord\StopWordRepository;
use SolrRestApiClient\Tests\BaseTestCase;


/**
 * Class StopWordRepositoryTestCase
 * @package SolrRestApiClient\Tests\Api\Client\Domain\StopWord
 */
class StopWordRepositoryTestCase extends BaseTestCase {
	/**
	 * @var StopWordDataMapper
	 */
	protected $dataMapper = null;

	/**
	 * @var \SolrRestApiClient\Api\Client\Domain\StopWord\StopWordRepository()
	 */
	protected $stopwordRepository;

	/**
	 * @return void
	 */
	public function setUp() {
		$this->dataMapper = new StopWordDataMapper();
		$this->stopwordRepository = $this->getMock('SolrRestApiClient\Api\Client\Domain\StopWord\StopWordRepository',array('executeDeleteRequest','executeGetRequest','executePostRequest'));
		$this->stopwordRepository->injectDataMapper($this->dataMapper);
	}

	/**
	 * @return void
	 */
	public function tearDown() {}

	/**
	 * @test
	 */
	public function canAddAll() {
		$stopwordCollection = new StopWordCollection();
		$stopword = new StopWord();
		$stopword->setWord('foo');
		$stopwordCollection->add($stopword);

		$expectedJson = '["foo"]';
		$responseMock = $this->getMock('Guzzle\Http\Message\Response',array('getBody','getStatusCode'), array(),'',false);
		$responseMock->expects($this->once())->method('getStatusCode')->will($this->returnValue(200));
		$this->stopwordRepository->expects($this->once())->method('executePostRequest')->with('solr/schema/analysis/stopwords/it',$expectedJson)->will(
			$this->returnValue($responseMock)
		);

		$result = $this->stopwordRepository->addAll($stopwordCollection, 'it');
		$this->assertTrue($result);
	}

	/**
	 * @test
	 */
	public function canGetAllStopwords() {
		$responseMock = $this->getMock('Guzzle\Http\Message\Response',array('getBody'), array(),'',false);

		$fixtureResponse = '{
			  "responseHeader":{
			    "status":0,
			    "QTime":1
			  },
			  "wordSet":{
			    "initArgs":{"ignoreCase":true},
			    "initializedOn":"2014-03-28T20:53:53.058Z",
			    "managedList":[
			      "a",
			      "an",
			      "and"
			     ]
			  }
			}';

		$responseMock->expects($this->once())->method('getBody')->will($this->returnValue(
			$fixtureResponse
		));
		$this->stopwordRepository->expects($this->once())->method('executeGetRequest')->with('solr/schema/analysis/stopwords/it')->will(
			$this->returnValue($responseMock)
		);

		$stopwordAll = $this->stopwordRepository->getAll("it");
		$this->assertInstanceOf('SolrRestApiClient\Api\Client\Domain\StopWord\StopWordCollection', $stopwordAll);
		$this->assertEquals(3, $stopwordAll->getCount(),'Unexpected amount of stopwords retrieved');
	}

	/**
	 * @test
	 */
	public function canDeleteAllStopWords() {
		$stopwordsCount = 5;
		$stopwordCollection = new StopWordCollection();

		for($i = 0; $i < $stopwordsCount; $i++) {
			$synonym = new StopWord();
			$synonym->setWord('foo');

			$stopwordCollection->add($synonym);
		}

		$this->stopwordRepository = $this->getMock('SolrRestApiClient\Api\Client\Domain\StopWord\StopWordRepository',array('executeDeleteRequest','executeGetRequest','executePostRequest', 'getAll', 'getTag'));
		$this->stopwordRepository->injectDataMapper($this->dataMapper);

		$this->stopwordRepository->expects($this->once())->method('getTag');
		$this->stopwordRepository->expects($this->once())->method('getAll')->will($this->returnValue(
			$stopwordCollection
		));

		$responseMock = $this->getMock('Guzzle\Http\Message\Response',array('getBody','getStatusCode'), array(),'',false);
		$responseMock->expects($this->exactly($stopwordsCount))->method('getStatusCode')->will($this->returnValue(200));

		$endpoint = 'solr/schema/analysis/stopwords//foo';
		$this->stopwordRepository->expects($this->exactly($stopwordsCount))->method('executeDeleteRequest')->with($endpoint)->will($this->returnValue(
			$responseMock
		));

		$this->assertTrue($this->stopwordRepository->deleteAll());
	}

	/**
	 * @test
	 */
	public function canDeleteByWord() {
		$responseMock = $this->getMock('Guzzle\Http\Message\Response',array('getBody'), array(),'',false);
		$this->stopwordRepository->expects($this->once())->method('executeDeleteRequest')->with('solr/schema/analysis/stopwords/it/test')->will(
			$this->returnValue($responseMock)
		);
		$this->stopwordRepository->deleteByWord('test',"it");
	}

	/**
	 * @test
	 */
	public function canGetByWord() {
		$stopwordCollection = new StopWordCollection();
		$stopword = new StopWord();
		$stopword->setWord('foo');
		$stopwordCollection->add($stopword);

		$expectedJson = '["foo"]';
		$responseMock = $this->getMock('Guzzle\Http\Message\Response',array('getBody','getStatusCode'), array(),'',false);
		$responseMock->expects($this->exactly(2))->method('getStatusCode')->will($this->returnValue(200));
		$this->stopwordRepository->expects($this->once())->method('executePostRequest')->with('solr/schema/analysis/stopwords/it',$expectedJson)->will(
			$this->returnValue($responseMock)
		);

		$response = $this->stopwordRepository->addAll($stopwordCollection, 'it');
		$this->assertTrue($response);


		$this->stopwordRepository->expects($this->once())->method('executeGetRequest')->with('solr/schema/analysis/stopwords/default/foo')->will(
			$this->returnValue($responseMock)
		);
		$foundedWord = $this->stopwordRepository->getByWord('foo');
		$this->assertEquals('foo', $foundedWord->getByIndex(0)->getWord(), "Word not found");
	}

	/**
	 * @test
	 */
	public function canGetNotExistingWord() {
		$responseMock = $this->getMock('Guzzle\Http\Message\Response',array('getBody','getStatusCode'), array(),'',false);
		$responseMock->expects($this->once())->method('getStatusCode')->will($this->returnValue(404));

		$this->stopwordRepository->expects($this->once())->method('executeGetRequest')->with('solr/schema/analysis/stopwords/default/foo')->will(
			$this->returnValue($responseMock)
		);
		$foundedWord = $this->stopwordRepository->getByWord('foo');
		$this->assertEquals(0, $foundedWord->getCount(), "Word should not exist");
	}
}