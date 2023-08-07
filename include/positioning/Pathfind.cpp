#include "Pathfind.hpp"

ObstacleManager Pathfind::collisionDetect = ObstacleManager{};
std::shared_ptr<Window> Pathfind::_window = nullptr;

Pathfind::Pathfind()
{
	
}

Pathfind::Pathfind(std::shared_ptr<Window> window) 
{
	_window = window;
	generator = AStar::Generator{_window};
}

std::vector<Vector> Pathfind::findPath(Vector start, Vector end)
{
	return generator.findPath(start, end);
}

// std::vector<Vector> Pathfind::reconstruct_path(const std::map<Vector, Vector>& cameFrom, Vector current)
// {
// 	std::vector<Vector> total_path = {current};
// 	while (cameFrom.count(current) > 0) {
// 		total_path.push_back(current);
// 	}
// 	std::reverse(total_path.begin(), total_path.end());

// 	// std::cout << "---FOUND PATH TO DESTINATION:---" << std::endl;
// 	// for (Vector element : total_path) {
// 	// 	std::cout << element << std::endl;
// 	// }
// 	// std::cout << "---FOUND BETTER PATH:---" << std::endl;
// 	total_path = optimizePath(total_path);
// 	// for (Vector element : total_path) {
// 	// 	std::cout << element << std::endl;
// 	// }
// 	return total_path;
// }

// std::vector<Vector> Pathfind::optimizePath(std::vector<Vector> unoptimizedPath) {
// 	std::vector<Vector> finalPath = {unoptimizedPath.front()};
// 	Vector currentStart = unoptimizedPath[0];
// 	Vector prevDirectTo = unoptimizedPath[0];
// 	unoptimizedPath.erase(unoptimizedPath.begin());
// 	for (Vector directTo : unoptimizedPath) {
// 		if (collisionDetect.checkForIntersect({currentStart, directTo})) {
// 			finalPath.push_back(prevDirectTo);
// 			currentStart = prevDirectTo;
// 		} else {
// 		}
// 		prevDirectTo = directTo;
// 	}
// 	finalPath.push_back(unoptimizedPath.back());
// 	return finalPath;
// }