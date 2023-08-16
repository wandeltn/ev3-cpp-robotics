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
    if (!generator.om.checkForIntersect({start, end})) {
        return std::vector<Vector>{end};
    }
    std::vector<Vector> cachedPath = readFromFile(start, end);
    if (cachedPath.size()) {
        return cachedPath;
    }

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

std::vector<Vector> Pathfind::reconstruct_path(std::vector<Vector> total_path)
{
    // while (cameFrom.count(current) > 0) {
    // 	current = cameFrom.at(current);
    // 	total_path.push_back(current);
    // }
    std::reverse(total_path.begin(), total_path.end());

    std::cout << "---FOUND PATH TO DESTINATION:---" << std::endl;
    for (Vector element : total_path) {
        std::cout << element << std::endl;
    }
    std::cout << "---FOUND BETTER PATH:---" << std::endl;
    total_path = optimizePath(total_path);
    for (Vector element : total_path) {
        std::cout << element << std::endl;
    }
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

bool Pathfind::checkIfInChache(Vector start, Vector end)
{
    std::ifstream ifs{"/home/robot/path_saves.txt"};

    if (!ifs.is_open()) {
        std::cout << "failed to read existing paths" << std::endl;
        return false;
    } else {
        std::cout << "reading existing paths" << std::endl;
    }
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

        std::regex slash{"[/]"};
        std::sregex_token_iterator first_slash{line.begin(), line.end(), slash, -1}, last_slash;
        std::vector<std::string> pair{first_slash, last_slash};

        std::regex semicolon{"[;]"};
        std::sregex_token_iterator first_semicolon{pair[0].begin(), pair[0].end(), semicolon, -1}, last_semicolon;
        std::vector<std::string> endPoints{first_semicolon, last_semicolon};

        std::vector<Vector> coordinates{};
        for (std::string point : endPoints) {
            std::regex comma{"[,]"};
            std::sregex_token_iterator first_comma{point.begin(), point.end(), comma, -1}, last_comma;
            std::vector<std::string> vector{first_comma, last_comma};
            coordinates.push_back({static_cast<double>(std::stoi(vector[0])), static_cast<double>(std::stoi(vector[1]))});
            std::cout << "found coordinates: " << coordinates.back() << std::endl;
        }

        if (
            coordinates.front() == start &&
            coordinates.back() == end
        ) {
            ifs.close();
            return true;
        } else {
            ifs.close();
        }
    }
    return false;
    ifs.close();
}

void Pathfind::saveToFile(Vector start, Vector end, std::vector<Vector> path) {
    if (checkIfInChache(start, end)) {
        return;
    }

    std::cout << "writing to file" << std::endl;

    std::ofstream ofs{"/home/robot/path_saves.txt", std::ios::ate | std::ios::app};

    if (!ofs.is_open()) {
        std::cout << "couldnt write path to file" << std::endl;
    }

    ofs << start.x << "," << start.y << ";" << end.x << "," << end.y << "/";
    for (Vector node : path) {
        ofs << node.x << "," << node.y << ";";
    }
    ofs << "\n";
    ofs.close();
}

std::vector<Vector> Pathfind::readFromFile(Vector start, Vector end) {
    if(!checkIfInChache(start, end)) {
        return std::vector<Vector>{};
    }

    std::ifstream ifs{"/home/robot/path_saves.txt"};
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

		std::regex slash{"[/]"};
		std::sregex_token_iterator first_slash{line.begin(), line.end(), slash, -1}, last_slash;
		std::vector<std::string> pair{first_slash, last_slash};

		std::regex semicolon{"[;]"};
		std::sregex_token_iterator first_semicolon{pair[0].begin(), pair[0].end(), semicolon, -1}, last_semicolon;
		std::vector<std::string> endPoints{first_semicolon, last_semicolon};

		std::vector<Vector> coordinates{};
		for (std::string point : endPoints) {
			std::regex comma{"[,]"};
			std::sregex_token_iterator first_comma{point.begin(), point.end(), comma, -1}, last_comma;
			std::vector<std::string> vector{first_comma, last_comma};
			coordinates.push_back({static_cast<double>(std::stoi(vector[0])), static_cast<double>(std::stoi(vector[1]))});
			std::cout << "found coordinates: " << coordinates.back() << std::endl;
		}

		if (
			coordinates.front() == start &&
			coordinates.back() == end
		) {
            std::vector<Vector> final_path{};
			std::sregex_token_iterator first{pair[1].begin(), pair[1].end(), semicolon, -1}, last;
            std::vector<std::string> path{first, last};
            for (std::string node : path) {
                std::regex comma{"[,]"};
			    std::sregex_token_iterator first_comma{node.begin(), node.end(), comma, -1}, last_comma;
			    std::vector<std::string> vector{first_comma, last_comma};
			    final_path.push_back({static_cast<double>(std::stoi(vector[0])), static_cast<double>(std::stoi(vector[1]))});
			    std::cout << "found coordinates: " << coordinates.back() << std::endl;
            }
            ifs.close();
            return final_path;
		} else {
            ifs.close();
        }

	}
    return std::vector<Vector>{};
}