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
    std::cout << "pathfinding from: " << start << " to: " << end << std::endl;


    if (!generator.om.checkForIntersect({start, end})) {
        return std::vector<Vector>{end};
    }
    std::vector<Vector> cachedPath = readFromFile(start, end);
    if (cachedPath.size()) {
        return cachedPath;
    } else {
        std::cout << "generating path" << std::endl;
        AStar::CoordinateList path = generator.findPath(start, end);
        std::cout << "finished generating" << std::endl;
        path = reconstruct_path(path);
        Vector prevNode = path.front();
        for (Vector node : path) {
            _window->drawLine(node, prevNode, DISPLAY_BLACK);
            prevNode = node;
        }
        std::cout << "saving to file" << std::endl;
        saveToFile(start, end, path);
        std::cout << "return" << std::endl;
        return path;
    }
}

std::vector<Vector> Pathfind::reconstruct_path(std::vector<Vector> total_path)
{
    std::reverse(total_path.begin(), total_path.end());

    // std::cout << "---FOUND PATH TO DESTINATION:---" << std::endl;
    // for (Vector element : total_path) {
        // std::cout << element << std::endl;
    // }
    // std::cout << "---FOUND BETTER PATH:---" << std::endl;
    total_path = optimizePath(total_path);
    // for (Vector element : total_path) {
        // std::cout << element << std::endl;
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

void Pathfind::saveToFile(Vector start, Vector end, std::vector<Vector> path) {
    if (readFromFile(start, end).size()) {
        return;
    }

    std::cout << "writing to file" << std::endl;

    std::ofstream ofs{"path_saves.txt", std::ios::ate | std::ios::app};

    if (!ofs.is_open()) {
        std::cout << "couldnt write path to file" << std::endl;
    }

    ofs << "\n" << start.x << "," << start.y << ";" << end.x << "," << end.y << "/";
    for (Vector node : path) {
        ofs << node.x << "," << node.y << ";";
    }
    ofs.close();
}

std::vector<Vector> Pathfind::readFromFile(Vector start, Vector end) {
    std::ifstream ifs{"path_saves.txt"};
    std::string line{};
    
    while(getline(ifs, line)) {
		line.erase(std::remove_if(
                    line.begin(),
                    line.end(),
                    [](unsigned char c){
                        return !std::isprint(c);
                    }),
                    line.end()
		); 
		std::cout << "read line: " << line << std::endl;

		std::vector<std::string> pair = explode(line, '/');
		std::vector<std::string> endPoints = explode(pair[0], ';');

		std::vector<Vector> coordinates{};
		for (std::string point : endPoints) {
			std::vector<std::string> vector = explode(point, ',');
			coordinates.push_back({static_cast<double>(std::stoi(vector[0])), static_cast<double>(std::stoi(vector[1]))});
		}

		if (
			coordinates.front() == start &&
			coordinates.back() == end
		) {
            std::vector<Vector> final_path{};
            std::vector<std::string> path = explode(pair[1], ';');
            for (std::string node : path) {
			    std::vector<std::string> vector = explode(node, ',');
			    final_path.push_back({static_cast<double>(std::stoi(vector[0])), static_cast<double>(std::stoi(vector[1]))});
            }
            ifs.close();
            return final_path;
		}
	}
    return std::vector<Vector>{};
}

std::vector<std::string> Pathfind::explode(const std::string &string, const char &c)
{
    std::string buff{""};
	std::vector<std::string> v;
	
	for(auto n:string)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}
