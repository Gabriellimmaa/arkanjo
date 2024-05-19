#ifndef SIMILARITY_TABLE_HPP
#define SIMILARITY_TABLE_HPP

#include <bits/stdc++.h> 

#include "path.hpp"
#include "utils.hpp"
using namespace std;

class Similarity_Table{
	private:
		string SIMILARITY_TABLE_FILE_NAME = "output_parsed.txt";
		double DEFAULT_SIMILARITY = 100.00;
		double EPS_ERROR_MARGIN = 1e-6;
		double MAXIMUM_SIMILARITY = 100.00;
		double MINIMUM_SIMILARITY = 0.00;

		double similarity_threshold;
		vector<Path> paths;
		map<Path,int> path_id;
		vector<vector<pair<int,double>>> similarity_graph;
		map<pair<int,int>,double> similarity_table;

		int find_id_path(Path path);
		void read_comparation(ifstream &table_file);
		void read_file_table(ifstream &table_file);
		void init_similarity_table();
		bool is_above_threshold(double similarity);

	public:
		Similarity_Table(double _similarity_threshold);
		Similarity_Table();
		
		void update_similarity(double new_similarity_threshold);
		double get_similarity(Path path1, Path path2);
		double is_similar(Path path1, Path path2);
		vector<Path> get_path_list();
		vector<Path> get_similar_path_to_the_reference(Path reference);
		vector<tuple<double,Path,Path>> get_all_path_pairs_and_similarity_sorted_by_similarity();
		vector<pair<Path,Path>> get_all_similar_path_pairs_sorted_by_similarity();
};

#endif
