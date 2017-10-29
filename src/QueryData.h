/*
 *
 * Developed by Alexander Hart
 * Plant Computational Genomics Lab
 * University of Connecticut
 *
 * For information, contact Alexander Hart at:
 *     entap.dev@gmail.com
 *
 * Copyright 2017, Alexander Hart, Dr. Jill Wegrzyn
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


#ifndef ENTAP_QUERYDATA_H
#define ENTAP_QUERYDATA_H


#include "QuerySequence.h"
#include "EntapExecute.h"

struct FrameStats {
    uint32 removed;
    uint32 selected;
    uint32 partial_5;
    uint32 partial_3;
    uint32 internal;
    uint32 complete;
};

class QueryData {

public:

    QueryData(std::string&, std::string&, bool&, bool&);
    ~QueryData();

    QUERY_MAP_T* get_sequences_ptr();

    void flag_transcripts(ExecuteStates);
    std::pair<uint16, uint16> calculate_N_vals(std::vector<uint16>&,uint64);
    std::pair<uint16, uint16> calculate_N_vals(ExecuteStates, bool);
    std::string trim_sequence_header(std::string&, std::string);
    void final_statistics(std::string&, std::vector<uint16>&);
    bool is_protein(void) const;
    void set_protein(bool);
    void set_frame_stats(const FrameStats &_frame_stats);
    void set_EXPRESSION_SUCCESS(bool _EXPRESSION_SUCCESS);
    void set_FRAME_SELECTION_SUCCESS(bool _FRAME_SELECTION_SUCCESS);
    void set_SIM_SEARCH_SUCCESS(bool _SIM_SEARCH_SUCCESS);
    void set_ONTOLOGY_SUCCESS(bool _ONTOLOGY_SUCCESS);

private:
    void set_input_type(std::string&);

    const uint8         LINE_COUNT   = 20;
    const uint8         NUCLEO_DEV   = 2;
    const fp32          N_50_PERCENT = 0.5;
    const fp32          N_90_PERCENT = 0.9;
    const std::string   NUCLEO_FLAG  = "Nucleotide";
    const std::string   PROTEIN_FLAG = "Protein";
    const std::string   COMPLETE_FLAG= "Complete";
    const std::map<char,uint8> NUCLEO_MAP{
            {'A', 1},
            {'G', 1},
            {'C', 1},
            {'T', 1}
    };
    const std::string OUT_UNANNOTATED_NUCL = "final_unannotated.fnn";
    const std::string OUT_UNANNOTATED_PROT = "final_unannotated.faa";
    const std::string OUT_ANNOTATED_NUCL   = "final_annotated.fnn";
    const std::string OUT_ANNOTATED_PROT   = "final_annotated.faa";

    QUERY_MAP_T  _SEQUENCES;
    bool         _trim;
    bool         _protein;
    bool         _EXPRESSION_SUCCESS;
    bool         _FRAME_SELECTION_SUCCESS;
    bool         _SIM_SEARCH_SUCCESS;
    bool         _ONTOLOGY_SUCCESS;
    uint32       _total_sequences;          // Original sequence number
    uint64       _start_nuc_len;            // Starting total len
    uint64       _start_prot_len;           // Starting total len
    FrameStats   _frame_stats;

};


#endif //ENTAP_QUERYDATA_H
