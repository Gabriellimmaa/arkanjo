#ifndef SIMILARITY_EXPLORER_HPP
#define SIMILARITY_EXPLORER_HPP

#include <bits/stdc++.h> 

#include "path.hpp"
#include "function.hpp"
#include "utils.hpp"
#include "similarity_table.hpp"
using namespace std;

class Similarity_Explorer{
	public:
		int UNLIMITED_RESULTS = 0;
		string EMPTY_PATTERN = "";
	private:
		string BETWEEN_RELATIVE_AND_FUNCTION_NAME = "::";
		string START_LINE_COMPARATION_PRINT = "Functions find: ";
		string BETWEEN_TWO_FUNCTION = " AND ";
		string NUMBER_LINES_MESSAGE = " , TOTAL NUMBER LINES IN FUNCTIONS: ";
		string INITIAL_TEXT_PRINT_1 = "It was found a total of ";
		string INITIAL_TEXT_PRINT_2 = " pair of duplicate functions in the codebase. Which the first ";
		string INITIAL_TEXT_PRINT_3 = " can be found below.";
		int INITIAL_PROCESSED_RESULTS = 0;

		Similarity_Table *similarity_table;
		int limit_on_results;
		string pattern_to_match;
		bool both_path_need_to_match_pattern;
		int processed_results = INITIAL_PROCESSED_RESULTS;

		Utils::COLOR choose_text_color();
		int find_number_pairs_show(int number_pair_found);
		string format_initial_message(int number_pair_found);
		bool match_pattern(Path path1, Path path2);
		string format_path_message_in_pair(Path path);
		int find_number_lines(Path path1);
		void print_similar_path_pair(Path path1, Path path2);
		void process_similar_path_pair(Path path1, Path path2);
		int find_number_pair_found(vector<pair<Path,Path>> similar_path_pairs);
		void explorer();

	public:
		Similarity_Explorer(Similarity_Table *_similarity_table, 
				int _limit_on_results, 
				string _pattern_to_match, 
				bool _both_path_need_to_match);
};

#endif
