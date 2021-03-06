.. _Boost: http://www.boost.org/users/download/
.. _Perl: https://www.perl.org/
.. _Python: https://www.python.org/
.. _RSEM: https://github.com/deweylab/RSEM
.. _EggNOG-Emapper: https://github.com/jhcepas/eggnog-mapper
.. _DIAMOND: https://github.com/bbuchfink/diamond
.. _GeneMarkS-T: http://exon.gatech.edu/GeneMark/
.. _CMake: https://cmake.org/
.. _InterProScan: https://github.com/ebi-pf-team/interproscan

Installation
==================
EnTAP is packaged with all of the software necessary to fully annotate a set of transcripts.  It is optimized to allow a single-command execution for all steps in the pathway, including paramterization by the user.  EnTAP does not have a graphical user interface but it does generate visual summaries for the user at each stage as well as detailed summary files and logs.   

#. :ref:`System Requirements<sys-label>`
#. :ref:`Dependency Check<dep-label>`
#. :ref:`Pipeline Software<pipe-label>`
#. :ref:`EnTAP<entap-label>`

Before full EnTAP installation, dependencies must be checked to see if they are included in your system (many are by default) and the accompanying pipeline software will need to be installed (unless is already present on the system).

.. sys-label:

System Requirements
-------------------
  
    * Operating System

        * UNIX-based systems
        * Tested on 64 bit systems: ubuntu 16.04, Rocks 6.1, Centos 6.3

    * Storage Minimum

        * Gene Ontology References: 6Mb
        * NCBI Taxonomy: 400Mb
        * EggNOG Database: 30Gb
        * DIAMOND Databases: ~13Gb (with RefSeq Complete Protein + Uniprot Swiss-Prot)
        * Additional storage for files generated depending on transcriptome size (at least 5 times the size)
        * Typical total: 48Gb (with a fully processed, 30,000 sequence transcriptome) 

    * Memory

        * At least 16 Gb of RAM (will very depending on DIAMOND database sizes)

.. _dep-label:

Dependency Check
------------------
Before continuing on in the installation process, ensure that the following dependencies are fully installed on your system:

    * C++11 compiler (GCC 4.8.1 or later)
	
    * CMake_ (2.8 or later)
	
    * Boost_ C++ Libraries (1.50 or later)
	
        * Ensure this is installed with the C++11 compiler
		
    * Python_ (2.7.12 or later) with support for the following modules
	
        * SQLITE
		
        * Matplotlib (figures generated by EnTAP)
		
    * Unix wget (generally included in most distros)
	
    * Unix gzip/tar (generally included in most distros)


.. _pipe-label:

Pipeline Software
------------------
EnTAP leverages several software distributions within the pipeline to provide the best quality annotations. The packages used (and their tested versions) can be seen below. This is not to say that newer versions will not be compatible, however they have not been tested yet with EnTAP. 

.. note:: If the software is already installed on your system, this stage can be skipped

Software:
    * RSEM_ (Expression Filtering with alignment file): version 1.3.0
    * GeneMarkS-T_ (Frame Selection): version 5.1
    * DIAMOND_ (Similarity Search): version 0.8.31
    * EggNOG-Emapper_ (Orthologous Group Assignment): version 0.7.4.1-beta
    * InterProScan_ (Protein Databases): This is not included within the EnTAP repo, but is supported 

If you have downloaded the full repository from the GitLab page, each of these (with the exception of GeneMarkS-T) are contained within the /libs directory. GeneMarkS-T must be acquired from the website linked previously due to licensing (free for academic use). 


RSEM and DIAMOND both require compilation from source code while EggNOG-Emapper or GeneMarkS-T does not. To compile these, run the script within the main directory: 

.. code-block :: bash

    ./setup.sh


This will make+install DIAMOND and make RSEM. 

.. warning:: Ensure that DIAMOND was properly installed (global installation required by EggNOG-Emapper)

If there are any problems with the setup script, installation steps can be found on the GitHub pages for each. 

.. _entap-label:

EnTAP Installation
----------------------

Once dependencies and pipeline software have been installed, you can now continue to install EnTAP! 

First, download and extract the latest release(tagged) version from GitLab:
https://gitlab.com/EnTAP/EnTAP/tags

Within the main directory, execute the following command:

.. code-block :: bash

    cmake CMakeLists.txt

This will generate a MakeFile. Then execute:

.. code-block :: bash

    make

Or to install to a destination directory:

.. code-block :: bash

    cmake CMakeLists.txt -DCMAKE_INSTALL_PREFIX=/destination/dir

.. code-block :: bash

    make install

This will complete the installation process. You are ready to start using EnTAP!
