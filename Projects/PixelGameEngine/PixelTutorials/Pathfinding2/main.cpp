#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <vector>
#include <list>
#include <algorithm>
#include <utility>

// Override base class with your custom functionality
class Pathfinding2 : public olc::PixelGameEngine
{
public:
	Pathfinding2()
	{
		// Name your application
		sAppName = "Pathfinding 2";
	}

private:

	int MapWidth;
	int MapHeight;
	int CellSize;
	int BorderWidth;

	bool* bObstacleMap;

	int* FlowFieldZ;
	float* FlowFieldY;
	float* FlowFieldX;

	int StartX;
	int StartY;
	int EndX;
	int EndY;

	int Wave = 1;

public:
	bool OnUserCreate() override
	{
		BorderWidth = 4;
		CellSize = 32;
		MapWidth = ScreenWidth() / CellSize;
		MapHeight = ScreenHeight() / CellSize;
		bObstacleMap = new bool[MapWidth * MapHeight]{ false };

		FlowFieldZ = new int[MapWidth * MapHeight]{ 0 };
		FlowFieldX = new float[MapWidth * MapHeight]{ 0 };
		FlowFieldY = new float[MapWidth * MapHeight]{ 0 };

		StartX = 3;
		StartY = 7;
		EndX = 12;
		EndY = 7;


		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Little convenience lambda 2D -> 1D
		auto P = [&](int x, int y) {return y * MapWidth + x; };

		// User Input
		int SelectedCellX = GetMouseX() / CellSize;
		int SelectedCellY = GetMouseY() / CellSize;

		if (GetMouse(0).bPressed)
		{
			//Toggle Obstacle if mouse left clicked
			bObstacleMap[P(SelectedCellX, SelectedCellY)] = !bObstacleMap[P(SelectedCellX, SelectedCellY)];

		}

		if (GetMouse(1).bReleased)
		{
			StartX = SelectedCellX;
			StartY = SelectedCellY;
		}

		if (GetKey(olc::Key::Q).bReleased)
		{
			Wave++;
		}

		if (GetKey(olc::Key::A).bReleased)
		{
			Wave--;
			if (Wave == 0)
				Wave = 1;
		}

		// 1) Prepare flow field, add a boundary, and add obstacles
		// by setting the flow Field height (Z) to -1
		for (int x = 0; x < MapWidth; x++)
		{
			for (int y = 0; y < MapHeight; y++) 
			{
				// Set Border or Obstacles
				if (x == 0 || y == 0 || x == (MapWidth - 1) || y == (MapHeight - 1) || bObstacleMap[P(x,y)])
				{
					FlowFieldZ[P(x, y)] = -1;
				}
				else
				{
					FlowFieldZ[P(x, y)] = 0;
				}
			}
		}

		// 2) Propagate a wave (i.e. flood-fill) from taget location. Here I use
		// a tuple, of {x,y, distance} - though you could use a struct or similar.
		std::list<std::tuple<int, int, int>> Nodes;

		// Add the first discovered node - the target location, with a distance of 1
		Nodes.push_back({ EndX, EndY, 1 });

		while (!Nodes.empty())
		{
			//Each iteration through the discovered nodes may create newly discovered nodes,
			// so I maintain a second list. It's important not to contaminate the list being iterated through.
			std::list<std::tuple<int, int, int>> NewNodes;

			// Now iterate through each discovered node. If it has neighbouring nodes
			// that are empty space and undiscovered, add those locations to the new nodes list
			for (auto& n : Nodes)
			{
				int x = std::get<0>(n); // Map X-Coordinate
				int y = std::get<1>(n); // Map Y-Coordinate
				int d = std::get<2>(n); // Distance from taget location

				// Set distance count for this node. Note that when we add nodes we add 1
				// to this distance. This emulates propagating a wave across the map, where
				// the front of that wave increments each iteration. In this way, we can
				// propagate distance information 'away from target location'
				FlowFieldZ[P(x, y)] = d;

				//Check East
				if ((x + 1) < MapWidth && FlowFieldZ[P(x + 1, y)] == 0)
				{
					NewNodes.push_back({ x + 1, y, d + 1 });
				}

				//Check East
				if ((x - 1) >= 0 && FlowFieldZ[P(x - 1, y)] == 0)
				{
					NewNodes.push_back({ x - 1, y, d + 1 });
				}

				//Check South
				if ((y + 1) < MapHeight && FlowFieldZ[P(x, y + 1)] == 0)
				{
					NewNodes.push_back({ x, y + 1, d + 1 });
				}

				//Check North
				if ((y - 1) >= 0 && FlowFieldZ[P(x, y - 1)] == 0)
				{
					NewNodes.push_back({ x, y - 1, d + 1 });
				}
			}

			// We will now have potentially multiple nodes for a single location. this means our algorithm will never complete!
			// So we must remove duplicates from our new node list.
			// Im doing this with some clever code - but it is not performant - just merely convenient.
			// I'd suggest doing away with overhead structures like linked lists and sorts
			// if you are aiming for fastest path finding.

			// Sort the nodes - This will stack up nodes that are similar
			NewNodes.sort([&](const std::tuple<int, int, int>& n1, const std::tuple<int, int, int>& n2)
				{
					//In this instance I dont care how the values are sorted, so long as nodes that represent the same location are adjacent in the list.
					// I can use the P() lambda to generate a unique 1D value for a 2D coordinate, so I'll sort by that.
					return P(std::get<0>(n1), std::get<1>(n1)) < P(std::get<0>(n2), std::get<1>(n2));
				});

			// Use "unique" function to remove adjacent duplicates and also erase them                                       
			NewNodes.unique([&](const std::tuple<int, int, int>& n1, const std::tuple<int, int, int>& n2)
				{
					return  P(std::get<0>(n1), std::get<1>(n1)) == P(std::get<0>(n2), std::get<1>(n2));
				});

			// We've now processed all the discoverd nodes, so clear the list, and add the newly
			// discovered nodes for processing on the next iteration
			Nodes.clear();
			Nodes.insert(Nodes.begin(), NewNodes.begin(), NewNodes.end());

			// When there are no more newly discovered nodes, we have "flood filled" the entire
			// map. The propagation phase of the algorithm is complete

		}

		// 3) Create Path. Starting at a start location, create a path of nodes until you reach target location.
		// At each node, find the neighbour with the lowest "distance" score.

		std::list<std::pair<int, int>> Path;
		Path.push_back({ StartX, StartY });
		int LocationX = StartX;
		int LocationY = StartY;
		bool bNoPath = false;

		while (!(LocationX == EndX && LocationY == EndY) && !bNoPath)
		{
			std::list<std::tuple<int, int, int>> Neighbours;

			// 4-Way Connectivity
			if ((LocationY - 1) >= 0 && FlowFieldZ[P(LocationX, LocationY - 1)] > 0)
				Neighbours.push_back({ LocationX, LocationY - 1, FlowFieldZ[P(LocationX, LocationY - 1)] });

			if ((LocationX + 1) < MapWidth && FlowFieldZ[P(LocationX + 1, LocationY)] > 0)
				Neighbours.push_back({ LocationX + 1, LocationY, FlowFieldZ[P(LocationX + 1, LocationY)] });

			if ((LocationY + 1) < MapHeight && FlowFieldZ[P(LocationX, LocationY + 1)] > 0)
				Neighbours.push_back({ LocationX, LocationY + 1, FlowFieldZ[P(LocationX, LocationY + 1)] });

			if ((LocationX - 1) >= 0 && FlowFieldZ[P(LocationX - 1, LocationY)] > 0)
				Neighbours.push_back({ LocationX - 1, LocationY, FlowFieldZ[P(LocationX - 1, LocationY)] });

			// 8-Way Connectivity
			if ((LocationY - 1) >= 0 && (LocationX - 1) >= 0 && FlowFieldZ[P(LocationX - 1, LocationY - 1)] > 0)
				Neighbours.push_back({ LocationX - 1, LocationY - 1, FlowFieldZ[P(LocationX - 1, LocationY - 1)] });

			if ((LocationY - 1) >= 0 && (LocationX + 1) < MapWidth && FlowFieldZ[P(LocationX + 1, LocationY - 1)] > 0)
				Neighbours.push_back({ LocationX + 1, LocationY - 1, FlowFieldZ[P(LocationX + 1, LocationY - 1)] });

			if ((LocationY + 1) < MapHeight && (LocationX - 1) >= 0 && FlowFieldZ[P(LocationX - 1, LocationY + 1)] > 0)
				Neighbours.push_back({ LocationX - 1, LocationY + 1, FlowFieldZ[P(LocationX - 1, LocationY + 1)] });

			if ((LocationY + 1) < MapHeight && (LocationX + 1) < MapWidth && FlowFieldZ[P(LocationX + 1, LocationY + 1)] > 0)
				Neighbours.push_back({ LocationX + 1, LocationY + 1, FlowFieldZ[P(LocationX + 1, LocationY + 1)] });

			// Sprt neigbours based on height, so lowest neighbour is at front
			// of list
			Neighbours.sort([&](const std::tuple<int, int, int>& n1, const std::tuple<int, int, int>& n2)
				{
					return std::get<2>(n1) < std::get<2>(n2); // Compare distances
				});

			if (Neighbours.empty()) // Neighbour is invalid or no possible path
				bNoPath = true;
			else
			{
				LocationX = std::get<0>(Neighbours.front());
				LocationY = std::get<1>(Neighbours.front());
				Path.push_back({ LocationX, LocationY });
			}
		}





		bool bFirstPoint = true;
		int ox;
		int oy;

		for (auto& a : Path)
		{
			if (bFirstPoint)
			{
				ox = a.first;
				oy = a.second;
				bFirstPoint = false;
			}
			else
			{
				DrawLine
				(
					ox * CellSize + ((CellSize - BorderWidth) / 2),
					oy * CellSize + ((CellSize - BorderWidth) / 2),
					a.first * CellSize + ((CellSize - BorderWidth) / 2),
					a.second * CellSize + ((CellSize - BorderWidth) / 2),
					olc::YELLOW
				);

				ox = a.first;
				oy = a.second;

				FillCircle
				(
					ox * CellSize + ((CellSize - BorderWidth) / 2),
					oy * CellSize + ((CellSize - BorderWidth) / 2),
					10,
					olc::YELLOW);
			}
		}



		//Draw Map
		Clear(olc::BLACK);

		for (int x = 0; x < MapWidth; x++)
		{
			for (int y = 0; y < MapHeight; y++)
			{
				olc::Pixel Colour = olc::BLUE;

				if (bObstacleMap[P(x, y)])
				{
					Colour = olc::GREY;
				}

				if (Wave == FlowFieldZ[P(x, y)])
				{
					Colour = olc::DARK_CYAN;
				}

				if (x == StartX && y == StartY)
				{
					Colour = olc::GREEN;
				}

				if (x == EndX && y == EndY)
				{
					Colour = olc::RED;
				}

				//Draw Base
				FillRect(x * CellSize, y * CellSize, CellSize - BorderWidth, CellSize - BorderWidth, Colour);

				//Draw "potential" or "distance" or "height"
				DrawString(x* CellSize, y* CellSize, std::to_string(FlowFieldZ[P(x, y)]), olc::WHITE);
			}
		}

		

		return true;
	}
};

int main()
{
	Pathfinding2 demo;
	if (demo.Construct(512, 480, 2, 2))
		demo.Start();
	return 0;
}