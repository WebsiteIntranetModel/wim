<?php

namespace SolrRestApiClient\Common;

/**
 * Class Factory
 *
 * @package Searchperience\Common
 */
class Factory {

	/**
	 * @param string $hostname
	 * @param int $port
	 * @param string $corePath
	 * @return \SolrRestApiClient\Api\Client\Domain\Synonym\SynonymRepository
	 */
	public static function getSynonymRepository($hostname = 'localhost', $port = 8080, $corePath = 'solr/') {
		$guzzle             = self::getPreparedGuzzleClient();
		$dataMapper         = new \SolrRestApiClient\Api\Client\Domain\Synonym\SynonymDataMapper();

		$synonymRepository  = new \SolrRestApiClient\Api\Client\Domain\Synonym\SynonymRepository();
		$synonymRepository->setHostName($hostname);
		$synonymRepository->setPort($port);
		$synonymRepository->setCorePath($corePath);
		$synonymRepository->injectRestClient($guzzle);
		$synonymRepository->injectDataMapper($dataMapper);
		$synonymRepository->setRestClientBaseUrl();

		return $synonymRepository;
	}

	/**
	 * @param string $hostname
	 * @param int $port
	 * @param string $corePath
	 * @return \SolrRestApiClient\Api\Client\Domain\StopWord\StopWordRepository
	 */
	public static function getStopWordRepository($hostname = 'localhost', $port = 8080, $corePath = 'solr/') {
		$guzzle             = self::getPreparedGuzzleClient();
		$dataMapper         = new \SolrRestApiClient\Api\Client\Domain\StopWord\StopWordDataMapper();

		$stopWordRepository  = new \SolrRestApiClient\Api\Client\Domain\StopWord\StopWordRepository();
		$stopWordRepository->setHostName($hostname);
		$stopWordRepository->setPort($port);
		$stopWordRepository->setCorePath($corePath);
		$stopWordRepository->injectRestClient($guzzle);
		$stopWordRepository->injectDataMapper($dataMapper);
		$stopWordRepository->setRestClientBaseUrl();

		return $stopWordRepository;
	}

	/**
	 * @param string $hostname
	 * @param int $port
	 * @param string $corePath
	 * @return \SolrRestApiClient\Api\Client\Domain\ManagedResource\ManagedResourceRepository
	 */
	public static function getManagedResourceRepository($hostname = 'localhost', $port = 8080, $corePath = 'solr/') {
		$guzzle = self::getPreparedGuzzleClient();
		$dataMapper = new \SolrRestApiClient\Api\Client\Domain\ManagedResource\ManagedResourceDataMapper();

		$managedResourceRepository = new \SolrRestApiClient\Api\Client\Domain\ManagedResource\ManagedResourceRepository();
		$managedResourceRepository->setHostName($hostname);
		$managedResourceRepository->setPort($port);
		$managedResourceRepository->setCorePath($corePath);
		$managedResourceRepository->injectRestClient($guzzle);
		$managedResourceRepository->injectDataMapper($dataMapper);
		$managedResourceRepository->setRestClientBaseUrl();

		return $managedResourceRepository;
	}

	/**
	 * @return \Guzzle\Http\Client
	 * @throws Exception\RuntimeException
	 */
	protected static function getPreparedGuzzleClient() {
		$guzzle = new \Guzzle\Http\Client();
		$guzzle->setConfig(array(
			'redirect.disable' => true
		));

		return $guzzle;
	}
}