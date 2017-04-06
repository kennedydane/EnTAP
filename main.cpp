#include <iostream>
#include <fstream>
#include <array>
#include <cstring>
#include <unordered_map>
#include <vector>
#include "EntapInit.h"
#include "ExceptionHandler.h"
#include "pstream.h"
#include "boost/program_options.hpp"
#include "EntapConsts.h"
#include "EntapExecute.h"

namespace boostPO = boost::program_options;

enum States {
    PARSE_ARGS          = 0x01,
    INIT_ENTAP          = 0x02,
    INIT_ENTAP_SUCCESS  = 0x04,
    EXECUTE_ENTAP       = 0x08
};

void print_msg(std::string);
void init_log();
std::unordered_map<std::string, std::string> parse_arguments_boost(int,const char**);
void state_summary(States);

States state;   // init

int main(int argc, const char** argv) {
    init_log();
    try {
        state = PARSE_ARGS;
        std::unordered_map<std::string, std::string> inputs = parse_arguments_boost(argc,argv);
        if (state == INIT_ENTAP) {
            entapInit::init_entap(inputs, "0+");  // todo state input 1x, user wants to start at 1 and stop
        } else if (state == EXECUTE_ENTAP) {
            entapExecute::execute_main(inputs);
        } else {
            print_msg("Error in parsing input data");
            return 1;
        }
    } catch (ExceptionHandler &e) {
        if (e.getErr_code()==ENTAP_ERR::E_SUCCESS) return 0;
        e.print_msg();
        state_summary(state);
        return 1;
    }
    return 0;
}

std::unordered_map<std::string, std::string> parse_arguments_boost(int argc, const char** argv) {
    std::string err_msg;
    std::unordered_map<std::string, std::string> input_map;
    print_msg("Parsing user input...");
    std::string ncbi_data, uniprot_data, data_path, input_file, exe_state;
    std::vector<std::string> contam_vec;
    // TODO do not change .entp filename warning
    // TODO specify an output path
    try {
        boostPO::options_description description("Options");
        // TODO separate out into main options and additional with defaults
        description.add_options()
                ("help,h", "help options")
                ("config", "Configure enTAP for execution later (complete this step first)")
                ("run", "Execute enTAP functionality")
                ("ncbi,N", boostPO::value<std::string>(&ncbi_data)->default_value(ENTAP_CONFIG::NCBI_DEFAULT),"Select which NCBI database you would like to download"
                        "\nref - RefSeq database...")
                ("uniprot,U", boostPO::value<std::string>(&uniprot_data)->default_value(ENTAP_CONFIG::INPUT_UNIPROT_DEFAULT),
                        "Select which Uniprot database you would like to download"
                        "\n100 - UniRef100...")
                //multiple entries
                ("database,d", boostPO::value<std::string>(&data_path),
                        "Provide the path to a separate database, however this "
                        "may prohibit taxonomic filtering.")
                ("version,v", "Display version number")
                ("contam,c", boostPO::value<std::vector<std::string>>(&contam_vec)->multitoken(),"Contaminant selection")
                ("state,s", boostPO::value<std::string>(&exe_state),"Select a state value")
                ("input,i",boostPO::value<std::string>(&input_file)->default_value(ENTAP_CONFIG::INPUT_FILE_PATH),
                 "Input transcriptome file");
//        boostPO::positional_options_description posOptions;
//        posOptions.add("config", 1);
//        posOptions.add("run", 1);
        boostPO::variables_map vm;

        try {
            boostPO::store(boostPO::command_line_parser(argc,argv).options(description)
                .run(),vm);
            boostPO::notify(vm);

            if (vm.count("help")) {
                std::cout << description<<std::endl<<std::endl;
                throw(ExceptionHandler("",ENTAP_ERR::E_SUCCESS));
            }
            bool is_config = (bool) vm.count("config");     // ignore 'config config'
            bool is_run = (bool) vm.count("run");

            if (!is_config && !is_run) {
                err_msg = "Either config option or run option are required";
                throw(ExceptionHandler(err_msg.c_str(),ENTAP_ERR::E_INPUT_PARSE));
            }
            if (is_config && is_run) {
                throw(ExceptionHandler("Cannot specify both config and run flags",
                                       ENTAP_ERR::E_INPUT_PARSE));
            }

            if (ncbi_data.compare("nr")!=0 && ncbi_data.compare("refseq")!=0) {
                err_msg = "Not a valid NCBI database";
                throw(ExceptionHandler(err_msg.c_str(),ENTAP_ERR::E_INPUT_PARSE));
            }
            if (uniprot_data.compare("ur90")!=0 && uniprot_data.compare("ur100")!=0 &&
                    uniprot_data.compare("trembl")!=0, uniprot_data.compare("swiss")) {
                err_msg = "Not a valid Uniprot database";
                throw(ExceptionHandler(err_msg.c_str(),ENTAP_ERR::E_INPUT_PARSE));
            }
            // TODO check unknown database

            if (is_run && !vm.count("input")) {
                throw ExceptionHandler("Missing input transcriptome file", ENTAP_ERR::E_INPUT_PARSE);
            }

//            std::vector<std::string> contam_vec;
//            if (vm.count("contam")) {
//                try {
//                    std::istringstream ss(contaminants);
//                    std::cout<<contaminants<<std::endl;
//                    std::string it;
//                    while (std::getline(ss, it, ',')) {
//                        contam_vec.push_back(it);
//                    }
//                    if (contam_vec.size()>10) {
//                        throw ExceptionHandler("",0);
//                    }
//                } catch (...) {
//                    throw ExceptionHandler("Contaminant selection is invalid",
//                                           ENTAP_ERR::E_INIT_INDX_DATA_NOT_FOUND);
//                }
//            }
            // todo ensure that the input file exists

            input_map.emplace("N",ncbi_data);
            input_map.emplace("U", uniprot_data);
            input_map.emplace("i", input_file);
//            input_map.emplace("c", contam_vec);       // format: fungi,eukarota

            if (is_config) {
                state = INIT_ENTAP;
            } else state = EXECUTE_ENTAP;
        } catch (boost::program_options::required_option& e) {
            std::cout<<"Required Option"<<std::endl;
        }
    }catch (boost::program_options::error& e){
        // Unknown input
        throw ExceptionHandler(e.what(),ENTAP_ERR::E_INPUT_PARSE);
    }

    print_msg("Success!");
    return input_map;
}

void init_log() {
    remove("debug.txt");
    print_msg("Start - enTAP");
}

void print_msg(std::string msg) {
    time_t rawtime;
    time(&rawtime);
    std::string date_time = ctime(&rawtime);
    std::ofstream log_file("debug.txt", std::ios::out | std::ios::app);
    log_file << date_time.substr(0, date_time.size() - 2)
                 + ": " + msg << std::endl;
    log_file.close();
}

void state_summary(States st) {
    switch (st) {
        case(PARSE_ARGS):
            break;
        default:
            break;
    }
}