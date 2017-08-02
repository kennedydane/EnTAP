//
// Created by harta on 3/29/17.
//

#ifndef ENTAP_QUERYSEQUENCE_H
#define ENTAP_QUERYSEQUENCE_H

#include <iostream>
#include <vector>
#include <string>
#include "Ontology.h"


class QuerySequence {
public:
    typedef std::map<std::string,std::vector<std::string>> go_struct;
    bool operator>(const QuerySequence& querySequence);
    void set_sim_search_results(std::string,std::string,std::string, double,int, int, int, int,int,
                  int, int, double, double, double, std::string);
    QuerySequence();
    QuerySequence(bool, std::string);
    friend void operator+(const QuerySequence &);
    void setQseqid(const std::string &qseqid);
    void setSequence(std::string&);
    // TODO switch to map results
    void set_eggnog_results(std::string,std::string,std::string,std::string,std::string,
                    std::string,std::string,std::string);
    void set_tax_score(std::string);

    const std::string &get_contam_type() const;
    void set_contam_type(const std::string &_contam_type);
    void set_is_informative(bool _is_informative);
    void setIs_better_hit(bool is_better_hit);
    bool isContaminant() const;
    void setContaminant(bool contaminant);
    void set_is_database_hit(bool _is_database_hit);
    void set_ontology_results(std::map<std::string,std::string>);
    std::string print_final_results(short,const std::vector<std::string>&,short);
    void set_lineage(const std::string &_lineage);
    void set_go_parsed(const go_struct &_go_parsed);
    void setSeq_length(unsigned long seq_length);
    void setFrame(const std::string &frame);
    void setSpecies(const std::string &species);
    unsigned long getSeq_length() const;
    const std::string &getFrame() const;
    bool isIs_protein() const;
    const std::string &get_species() const;
    bool is_informative() const;
    const std::string &get_sequence_p() const;
    void set_sequence_p(const std::string &_sequence_p);
    const std::string &get_sequence_n() const;
    void set_sequence_n(const std::string &_sequence_n);
    const std::string &get_sequence() const;
    void setIs_protein(bool is_protein);
    bool is_is_database_hit() const;
    bool is_is_family_assigned() const;
    void set_is_family_assigned(bool _is_family_assigned);
    bool is_is_one_go() const;
    void set_is_one_go(bool _is_one_go);
    bool is_is_one_kegg() const;
    void set_is_one_kegg(bool _is_one_kegg);
    bool is_is_expression_kept() const;
    void set_is_expression_kept(bool _is_expression_kept);

private:

    static constexpr unsigned char E_VAL_DIF     = 8;
    static constexpr unsigned char COV_DIF       = 5;
    static constexpr unsigned char INFORM_ADD    = 3;
    static constexpr float INFORM_FACTOR         = 1.2;

    bool                              _contaminant;
    bool                              is_protein;
    bool                              is_better_hit;
    bool                              _is_informative;
    bool                              _is_database_hit;
    bool                              _is_family_assigned;
    bool                              _is_one_go;
    bool                              _is_one_kegg;
    bool                              _is_expression_kept;
    int                               _tax_id;
    int                               _length;
    int                               _mismatch;
    int                               _gapopen;
    int                               _qstart;
    int                               _qend;
    int                               _sstart;
    int                               _send;
    float                              _tax_score;
    unsigned long                     _seq_length;
    double                            _pident;
    double                            _bit_score;
    double                            _e_val;
    double                            _coverage;
    std::map<std::string,std::string> _ontology_results;
    std::vector<std::string>          _go_terms;
    std::vector<std::string>          _kegg_terms;
    go_struct                         _go_parsed;

    //TODO switch to map of sim search results
    std::string _database_path, _qseqid,_sseqid, _stitle, _species, _sequence_p, _sequence_n, _frame, _contam_type,
            _seed_ortho,_seed_eval,_seed_score,_predicted_gene,_tax_scope, _ogs,_go_str,_kegg_str,
            _lineage;

    friend std::ostream& operator<<(std::ostream& , const QuerySequence&);
    void init_sequence();
    unsigned long calc_seq_length(std::string &,bool);
};


#endif //ENTAP_QUERYSEQUENCE_H
