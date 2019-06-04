<?php

namespace SolrRestApiClient\Api\Client\Domain;

/**
 * Class AbstractRepository
 *
 * @author Timo Schmidt <timo.schmidt@aoe.com>
 * @package SolrRestApiClient\Api\Client\Domain
 */
abstract class AbstractRepository {

	/**
	 * @var \Guzzle\Http\Client
	 */
	protected $restClient;

	/**
	 * @var \SolrRestApiClient\Api\Client\Domain\JsonDataMapperInterface
	 */
	protected $dataMapper;

	/**
	 * @var string
	 */
	protected $hostName = 'localhost';

	/**
	 * @var int
	 */
	protected $port = 8080;

	/**
	 * @var string
	 */
	protected $corePath = 'solr/';

	/**
	 * @var array
	 */
	protected $headers = array('Content-type' => 'application/json');

	/**
	 * @var string
	 */
	protected $restEndPointPath  = '';

	/**
	 * @return string
	 */
	public function getCorePath() {
		return $this->corePath;
	}

	/**
	 * @param string $corePath
	 */
	public function setCorePath($corePath) {
		$this->corePath = $corePath;
	}

	/**
	 * @return string
	 */
	public function getHostName() {
		return $this->hostName;
	}

	/**
	 * @param string $hostName
	 */
	public function setHostName($hostName) {
		$this->hostName = $hostName;
	}

	/**
	 * @return int
	 */
	public function getPort() {
		return $this->port;
	}

	/**
	 * @param int $port
	 */
	public function setPort($port) {
		$this->port = $port;
	}

	/**
	 * @return string
	 */
	public function getRestEndPointPath() {
		return $this->restEndPointPath;
	}

	/**
	 * @param string $restEndPointPath
	 */
	public function setRestEndPointPath($restEndPointPath) {
		$this->restEndPointPath = $restEndPointPath;
	}

	/**
	 * @param \Guzzle\Http\Client $restClient
	 * @return void
	 */
	public function injectRestClient(\Guzzle\Http\Client $restClient) {
		$this->restClient = $restClient;
	}

	/**
	 * @return string
	 */
	public function getBaseUrl() {
		return 'http://'.$this->hostName.':'.$this->port.'/';
	}

	/**
	 * @param array $arguments
	 * @return string
	 */
	protected function getEndpoint($arguments = array()) {
		$argumentsString = implode("/",$arguments);
		return $this->corePath . $this->restEndPointPath . $argumentsString;
	}

	/**
	 * @return void
	 */
	public function setRestClientBaseUrl() {
		$this->restClient->setBaseUrl($this->getBaseUrl());
	}

	/**
	 * @param $endpoint
	 * @param null $body
	 * @param array $options
	 * @return \Guzzle\Http\Message\Response
	 */
	protected function executePostRequest($endpoint, $body = null, $options = array()) {
		$response = $this->restClient->post($endpoint, $this->headers, $body, $options)->send();
		return $response;
	}

	/**
	 * @param $endpoint
	 * @param array $options
	 * @return \Guzzle\Http\Message\Response
	 */
	protected function executeGetRequest($endpoint, $options = array()) {
		$response = $this->restClient->get($endpoint, $this->headers, $options)->send();
		return $response;
	}

	/**
	 * @param string $endpoint
	 * @param array $options
	 * @return \Guzzle\Http\Message\Response
	 */
	protected function executeDeleteRequest($endpoint, $options = array()) {
		$response = $this->restClient->delete($endpoint, $this->headers, $options)->send();
		return $response;
	}
}

