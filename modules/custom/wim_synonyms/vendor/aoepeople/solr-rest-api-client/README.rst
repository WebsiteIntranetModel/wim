++++++++++++++++++++++++
Solr RESTApi Client
++++++++++++++++++++++++

:Author: Timo Schmidt <timo.schmidt@aoe.com>
:Author: AOE <dev@aoe.com>
:Description: PHP Library to communicate with the RestFul API of Apache Solr
:Homepage: http://www.searchperience.com/
:Build status: |buildStatusIcon|

Foreword
========================

With appearance of SOLR [Managed Resources](https://cwiki.apache.org/confluence/display/solr/Managed+Resources) feature,
our intention was to implement tiny and easy to use PHP API client to communicate to SOLR REST API interface.


Solr client basics
========================

The solr rest api client can be used to manage the following solr entities with the solr rest api:

* Synonyms
* Stopwords
* Managed Resources


Synonyms
======================

In solr you can configure a "managed" synonym with the following entry in your schema.xml:

::

     <filter class="org.apache.solr.rest.schema.analysis.ManagedSynonymFilterFactory" managed="mytag" />
::

When you have defined a managed synonym list as described below you can see it in the list of the manged
resources (e.g.: http://localhost:8080/<core/collectionpath>/schema/managed) and manage it with the solr rest api


The following example shows how you can used the api client to manage synonyms with a certain tag:

::

    require '<vendorDir>/vendor/autoload.php';

    $factory = new \SolrRestApiClient\Common\Factory();
    $repository = $factory->getSynonymRepository('localhost',8080,'solr/<yourcore>/');

    $synonymCollection = new \SolrRestApiClient\Api\Client\Domain\Synonym\SynonymCollection();

    $synonym = new \SolrRestApiClient\Api\Client\Domain\Synonym\Synonym();
    $synonym->setMainWord('foo');
    $synonym->addWordsWithSameMeaning('bar');
    $synonym->addWordsWithSameMeaning('bla');

    $synonymCollection->add($synonym);

    $result = $repository->addAll($synonymCollection,'mytag');
::

Stopwords
======================

In solr you can configure a "managed" stopwords with the following entry in your schema.xml:

::

     <filter class="solr.ManagedStopFilterFactory" managed="french" />
::

When you have defined a managed stopwords list as described below you can see it in the list of the manged
resources (e.g.: http://localhost:8080/<core/collectionpath>/schema/managed) and manage it with the solr rest api


The following example shows how you can use the api client to manage stopwords with a certain tag:

::

    require '<vendorDir>/vendor/autoload.php';

    $factory = new \SolrRestApiClient\Common\Factory();
    $repository = $factory->getStopWordRepository('localhost',8080,'solr/<yourcore>/');

    $stopwordCollection = new \SolrRestApiClient\Api\Client\Domain\StopWord\StopWordCollection();

    $stopword = new \SolrRestApiClient\Api\Client\Domain\StopWord\StopWord();
    $stopword->setWord('foo');

    $stopwordCollection->add($stopword);

    $result = $repository->addAll($stopwordCollection, 'french');
::

In addition to addAll method some other methods exist in repository like:

- getAll;
- getByWord;
- deleteAll;
- deleteByWord;


Managed Resources
======================

Some resources in solr (e.g. synonyms and stopwords) can be managed as managed resources.
To be able to read and write them you need to be able to get them from the solr server.

To manage this, you can use the ManagedResourceRepository.

The following example shows how to get all synonym resources and add a synonym collection
to all of them:

::

    require '<vendorDir>/vendor/autoload.php';

    $factory = new \SolrRestApiClient\Common\Factory();
    $managedResourceRepository  = $factory->getManagedResourceRepository('localhost',8080,'solr/<core/collection>/');
    $resources                  = $managedResourceRepository->getAll();

    $synonymRepository          = $factory->getSynonymRepository('localhost',8080,'solr/<core/collection>/');
    $synonymResources           = $resources->getSynonymResources();

    foreach($synonymResources as $synonymResource) {
	    $synonymRepository->setResource($synonymResource);

    	$synonymCollection = new \SolrRestApiClient\Api\Client\Domain\Synonym\SynonymCollection();

    	$synonym = new \SolrRestApiClient\Api\Client\Domain\Synonym\Synonym();
    	$synonym->setMainWord("one");
    	$synonym->addWordsWithSameMeaning("one#one");
    	$synonym->addWordsWithSameMeaning("one#two");
    	$synonymCollection->add($synonym);

    	$synonymRepository->addAll($synonymCollection);
    }


.. |buildStatusIcon| image:: https://secure.travis-ci.org/timoschmidt/solr-rest-api-client.png?branch=master
   :alt: Build Status
       :target: http://travis-ci.org/timoschmidt/solr-rest-api-client
