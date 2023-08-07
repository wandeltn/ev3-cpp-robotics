#include "Pathfind.hpp"

std::shared_ptr<Window> Pathfind::_window = nullptr;
bool Pathfind::_useWindow = false;
AStar::Generator Pathfind::generator;

Pathfind::Pathfind()
{

}

Pathfind::Pathfind(std::shared_ptr<Window> window) 
{
	_window = window;
	// _window->clearScreen();
	_useWindow = true;
	generator = AStar::Generator{window};
}

std::vector<Vector> Pathfind::findPath(Vector start, Vector end)
{
	AStar::CoordinateList path = generator.findPath(start, end);
	reconstruct_path(path, end);
	Vector prevNode = path.front();
	for (Vector node : path) {
		_window->drawLine(node, prevNode, DISPLAY_BLACK);
		prevNode = node;
	}
	return path;
}

std::vector<Vector> Pathfind::reconstruct_path(const std::vector<Vector>& cameFrom, Vector current)
{
	std::vector<Vector> total_path = {current};
	// while (cameFrom.count(current) > 0) {
	// 	current = cameFrom.at(current);
	// 	total_path.push_back(current);
	// }
	std::reverse(total_path.begin(), total_path.end());

	// std::cout << "---FOUND PATH TO DESTINATION:---" << std::endl;
	// for (Vector element : total_path) {
	// 	std::cout << element << std::endl;
	// }
	// std::cout << "---FOUND BETTER PATH:---" << std::endl;
	total_path = optimizePath(total_path);
	// for (Vector element : total_path) {
	// 	std::cout << element << std::endl;
	// }
	return total_path;
}

std::vector<Vector> Pathfind::optimizePath(std::vector<Vector> unoptimizedPath) {
	std::vector<Vector> finalPath = {};
	Vector currentStart = unoptimizedPath[0];
	Vector prevDirectTo = unoptimizedPath[0];
	unoptimizedPath.erase(unoptimizedPath.begin());
	for (Vector directTo : unoptimizedPath) {
		if (collisionDetect.checkForIntersect({currentStart, directTo})) {
			finalPath.push_back(prevDirectTo);
			currentStart = prevDirectTo;
		} else {
		}
		prevDirectTo = directTo;
	}
	finalPath.push_back(unoptimizedPath.back());
	return finalPath;
}