/*
 *
 * Developed by Alexander Hart
 * Plant Computational Genomics Lab
 * University of Connecticut
 *
 * For information, contact Alexander Hart at:
 *     entap.dev@gmail.com
 *
 * Copyright 2017-2018, Alexander Hart, Dr. Jill Wegrzyn
 *
 * This file is part of EnTAP.
 *
 * EnTAP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EnTAP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EnTAP.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef ENTAP_ABSTRACTFRAME_H
#define ENTAP_ABSTRACTFRAME_H

//*********************** Includes *****************************
#include "../QuerySequence.h"
#include "../QueryData.h"
//**************************************************************

/**
 * ======================================================================
 * Class AbstractFrame
 *
 * Description          - Abstract class/functions for Frame Selection
 *                        portion of pipeline
 *                      - New modules will inherit from this class and
 *                        implement it's functions to fit into pipeline
 *
 * Notes                - None
 *
 *
 * @return              - None
 * ======================================================================
 */
class AbstractFrame {

public:

/**
 * ======================================================================
 * Function AbstractFrame(std::string &exe, std::string &out,
 *                        std::string &in, std::string &proc,
                          std::string &fig, std::string &frame,
                          GraphingManager *graphing, QueryData *queryData)
 *
 * Description          - Constructor for Abstract frame selection class
 *                      - Initializes protected member variables for
 *                        expression modules
 *
 * Notes                - Constructor
 *
 * @param exe           - Path to execution directory (EnTAP, unused)
 * @param out           - Path to main outfiles directory (unused)
 * @param in            - Path to filtered transcriptome
 * @param proc          - Path to processed directory (within genemark for now)
 * @param frame         - Path to figure directory (within genemark for now)
 * @param graphing      - Ptr to graphing manager
 * @param query         - Ptr to query data
 *
 * @return              - None
 * ======================================================================
 */
    AbstractFrame(std::string &exe, std::string &in,
                  std::string &frame,
                  EntapDataPtrs &entap_data){
        _exe_path        = exe;
        _inpath          = in;
        _frame_outpath   = frame;
        _pGraphingManager = entap_data._pGraphingManager;
        _pQUERY_DATA      = entap_data._pQueryData;
        _pUserInput       = entap_data._pUserInput;
        _pFileSystem      = entap_data._pFileSystem;

        _processed_path = PATHS(frame, PROCESSED_DIR);
        _figure_path    = PATHS(frame, FIGURE_DIR);
        _pFileSystem->delete_dir(_processed_path);
        _pFileSystem->delete_dir(_figure_path);
        _pFileSystem->create_dir(_processed_path);
        _pFileSystem->create_dir(_figure_path);
    }

    virtual ~AbstractFrame() = default;
    virtual std::pair<bool, std::string> verify_files()=0;
    virtual std::string execute() = 0;
    virtual void parse() = 0;


protected:
    std::string     _exe_path;
    std::string     _outpath;
    std::string     _inpath;
    std::string     _processed_path;
    std::string     _figure_path;
    std::string     _frame_outpath;
    GraphingManager *_pGraphingManager;
    QueryData       *_pQUERY_DATA;
    FileSystem      *_pFileSystem;
    UserInput       *_pUserInput;

    const std::string PROCESSED_DIR                 = "processed/";
    const std::string FIGURE_DIR                    = "figures/";
};


#endif //ENTAP_ABSTRACTFRAME_H
