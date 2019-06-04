<?php

require '../vendor/autoload.php';

$factory                    = new \SolrRestApiClient\Common\Factory();
$managedResourceRepository  = $factory->getManagedResourceRepository('localhost',8080,'solr/<collection/corename>/');
$resources                  = $managedResourceRepository->getAll();

$synonymRepository          = $factory->getSynonymRepository('localhost',8080,'solr/<collection/corename>/');
$stopWordRepository         = $factory->getStopWordRepository('localhost',8080,'solr/<collection/corename>/');

foreach($resources->getSynonymResources() as $resource) {
	$synonymRepository->setResource($resource);

	$synonymCollection = new \SolrRestApiClient\Api\Client\Domain\Synonym\SynonymCollection();

	$synonym = new \SolrRestApiClient\Api\Client\Domain\Synonym\Synonym();
	$synonym->setMainWord("one");
	$synonym->addWordsWithSameMeaning("one#one");
	$synonym->addWordsWithSameMeaning("one#two");
	$synonymCollection->add($synonym);

	$synonym = new \SolrRestApiClient\Api\Client\Domain\Synonym\Synonym();
	$synonym->setMainWord("two");
	$synonym->addWordsWithSameMeaning("two#one");
	$synonym->addWordsWithSameMeaning("two#two");
	$synonymCollection->add($synonym);

	$synonymRepository->addAll($synonymCollection);
	$synonymRepository->deleteByMainWord("one");

	$synonymRepository->deleteAll();


	$stopWord = new \SolrRestApiClient\Api\Client\Domain\StopWord\StopWord();
	$stopWord->setWord("Arsch");

	$stopWordCollection = new \SolrRestApiClient\Api\Client\Domain\StopWord\StopWordCollection();
	$stopWordCollection->add($stopWord);

	$stopWordRepository->setResource($resource);
	$stopWordRepository->addAll($stopWordCollection);

	$allStopWords = $stopWordRepository->getAll();

	var_dump($allStopWords->getCount());

}

