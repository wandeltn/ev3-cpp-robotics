#include "Pathfind.hpp"

std::shared_ptr<Window> Pathfind::_window = nullptr;

Pathfind::Pathfind()
{

}

Pathfind::Pathfind(std::shared_ptr<Window> window) 
{
	_window = window;
	_window->clearScreen();
}

std::vector<Vector> Pathfind::findPath(Vector start, Vector end)
{
	std::array<Vector, 4> directions = {
		Vector{ 0, 1 }, 
		Vector{ 1, 0 },
		Vector{ 0, -1 },
		Vector{ -1, 0 }
		//Vector{ -1, -1 },
		//Vector{ 1, 1 },
		//Vector{ -1, 1 },
		//Vector{ 1, -1 }
	};

    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
	std::vector<Vector> openSet = { start };

	// For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from the start
    // to n currently known.
	std::map<Vector, Vector> cameFrom{};

	// For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
	std::map<Vector, double> gScore;
	gScore[start] = 0.0;

	// For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how cheap a path could be from start to finish if it goes through n.
	std::map<Vector, double> fScore;
	fScore[start] = start.getDistanceTo(end);

	while (!openSet.empty()) {
		Vector current = { 0,0 };
		double currentBestFScore = std::numeric_limits<double>::max();
		for (Vector openNode : openSet) {
			// if (fScore.count(openNode) == 0) {
			// 	fScore[openNode] = gScore[openNode] + openNode.getDistanceTo(end);
			// }
			if (fScore[openNode] < currentBestFScore) {
				current = openNode;
				currentBestFScore = fScore[openNode];
			}
		}
		_window->drawPixel(current, DISPLAY_LIGHT);
		if (_window != nullptr) {
		} else {
			// std::cout << current << std::endl;
		}

		if (current == end) {
			std::vector<Vector> final_path = reconstruct_path(cameFrom, current);
				Vector prevNode = final_path.front();
				_window->drawLine(final_path.back(), prevNode, DISPLAY_BLACK);
				for (Vector node : final_path) {
				}
			if (_window != nullptr) {
			}
			
			return final_path;
		}

		openSet.erase(std::remove(openSet.begin(), openSet.end(), current), openSet.end());

		for (Vector neighborDirection : directions) {
			Vector neighbor = current + neighborDirection;
			if (gScore.count(current) == 0) {
				gScore[current] = std::numeric_limits<double>::infinity();
			}
			if (gScore.count(neighbor) == 0) {
				gScore[neighbor] = std::numeric_limits<double>::infinity();
			}
			if (collisionDetect.checkForIntersect({current, neighbor})) {
				continue;
			}

			double tentative_gScore = gScore[current] + (current.getDistanceTo(neighbor));

			if (tentative_gScore < gScore[neighbor]) {
				cameFrom[neighbor] = current;
				gScore[neighbor] = tentative_gScore;
				fScore[neighbor] = tentative_gScore + neighbor.getDistanceTo(end);

				if (!std::count(openSet.begin(), openSet.end(), neighbor)) {
					openSet.push_back(neighbor);
				}
			}
		}
	}
	return std::vector<Vector>{};
}

std::vector<Vector> Pathfind::reconstruct_path(const std::map<Vector, Vector>& cameFrom, Vector current)
{
	std::vector<Vector> total_path = {current};
	while (cameFrom.count(current) > 0) {
		current = cameFrom.at(current);
		total_path.push_back(current);
	}
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