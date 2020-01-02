#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

template <typename T>
class Tree
{
	using adj_list_t = std::unordered_map<std::string, std::vector<std::string>>;

private:
	struct Node {
		Node(const T& value) : value(value), left(nullptr), right(nullptr) {}
		T value;
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;
	};
	std::shared_ptr<Node> root_;
	void populate_tree(std::shared_ptr<Node>& node, adj_list_t& adj_list, const T& value) {
		node = std::make_shared<Node>(value);
		for (auto child : adj_list[value]) {
			if (node->left) {
				populate_tree(node->right, adj_list, child);
			}
			else {
				populate_tree(node->left, adj_list, child);
			}
		}
	}
	int get_num_orbits(std::shared_ptr<Node> node, std::unordered_map<std::shared_ptr<Node>, bool>& visited, int depth) {
		if (visited[node]) return 0;
		visited[node] = true;
		return depth + (node->left ? get_num_orbits(node->left, visited, depth + 1) : 0) +
			(node->right ? get_num_orbits(node->right, visited, depth + 1) : 0);
	}

public:
	Tree(adj_list_t& adj_list, const T& starting_object) : root_(nullptr) {
		populate_tree(root_, adj_list, starting_object);
	}
	int get_num_orbits() {
		std::unordered_map<std::shared_ptr<Node>, bool> visited;
		return get_num_orbits(root_, visited, 0);
	}
};

