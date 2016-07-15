/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include "bfs_config.h"
#include "bfs_impl.h"
#include "bfs_point.h"

#include <map>
#include <list>
#include <algorithm>

void bfs_search_all(const struct point start,
		std::list<std::list<struct point> > &all_path,
		PathAssert PA, FoundAssert FA)
{
	std::map<int, int> came_from;
	std::list<int> open_list;
	std::list<int> close_list;
	std::list<int> target_found;

	open_list.push_back(UUID(start));

	while (!open_list.empty()) {
		int front_uuid = open_list.front();
		const struct point front = POINT(front_uuid);

		/* found a new target path */
		if (std::find(target_found.begin(), target_found.end(), front_uuid)
				== target_found.end() && FA(front)) {

			std::list<struct point> path;
			std::map<int, int>::const_iterator it;
			std::map<int, int>::const_iterator end = came_from.end();
			int back_start_uuid = open_list.front();

			while ((it = came_from.find(back_start_uuid)) != end) {
				path.push_back(POINT(it->first));
				back_start_uuid = it->second;
			}
			std::reverse(path.begin(), path.end());

			all_path.push_back(path);
			target_found.push_back(front_uuid);
		}

		const struct point neighbors[] = {
			UP(front),
			DOWN(front),
			LEFT(front),
			RIGHT(front)
		};

		for (unsigned int i = 0; i < BFS_ARRAY_LENGTH(neighbors); i++) {
			int neighbor_uuid = UUID(neighbors[i]);

			if (!PA(neighbors[i]) && !FA(neighbors[i]))
				continue;

			if (std::find(open_list.begin(), open_list.end(), neighbor_uuid)
					!= open_list.end())
				continue;

			if (std::find(close_list.begin(), close_list.end(), neighbor_uuid)
					!= close_list.end())
				continue;

			came_from[neighbor_uuid] = front_uuid;
			open_list.push_back(neighbor_uuid);
		}

		close_list.push_back(front_uuid);
		open_list.pop_front();
	}
}
