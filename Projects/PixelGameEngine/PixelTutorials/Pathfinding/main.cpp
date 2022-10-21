#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// Override base class with your custom functionality
class FPathfinding : public olc::PixelGameEngine
{
public:
	FPathfinding()
	{
		sAppName = "Pathfinding";
	}

private:

	struct FNode
	{
		bool bObstacle = false;
		bool bVisited = false;

		float GlobalGoal;
		float LocalGoal;

		int x;
		int y;

		std::vector<FNode*> Neighbors;

		FNode* Parent;
	};

	FNode* Nodes = nullptr;

	const int NodeSize = 9;
	const int NodeBorder = 2;
	int NodeInner = NodeSize - (NodeBorder * 2);

	const int MapWidth = 16;
	const int MapHeight = 16;

	FNode* StartNode = nullptr;
	FNode* EndNode = nullptr;

public:

	//-------------------------------------------------------------------------------------------
	bool OnUserCreate() override
	{
		//Dynamic Memory
		Nodes = new FNode[MapWidth * MapHeight];

		//Initial Setup
		InitializeNodes();

		//Create connections - in this case nodes are on a regular grid
		CreateConnections();

		//Manually positon the start and end markers so they are not null
		StartNode = &Nodes[(MapHeight / 2) * MapWidth + 1];
		EndNode = &Nodes[(MapHeight / 2) * MapWidth + MapWidth - 2];

		return true;
	}

	//-------------------------------------------------------------------------------------------
	bool OnUserUpdate(float ElapsedTime) override
	{
		//Update the grid according to mouse input
		UpdateGridStates();

		//Clear Screen
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

		//Draw Connections First - lines from this nodes position to its connected neighbour node positions
		DrawConnections();

		//Draw Nodes on top
		DrawNodes();

		//Draw Path by starting at the end, and following the parent node trail back to the start - the start node will not have a parent path to follow
		DrawPath();

		return true;
	}

private:
	
	//-------------------------------------------------------------------------------------------
	void InitializeNodes()
	{
		for (int x = 0; x < MapWidth; x++)
		{
			for (int y = 0; y < MapHeight; y++)
			{
				Nodes[y * MapWidth + x].x = x;
				Nodes[y * MapWidth + x].y = y;

				Nodes[y * MapWidth + x].bObstacle = false;
				Nodes[y * MapWidth + x].Parent = nullptr;
				Nodes[y * MapWidth + x].bVisited = false;
			}
		}
	}

	//-------------------------------------------------------------------------------------------
	void CreateConnections()
	{
		for (int x = 0; x < MapWidth; x++)
		{
			for (int y = 0; y < MapHeight; y++)
			{
				//Either of these can be commented out. Commenting out both technically also works.

				ConnectOrthogonally(x, y);

				ConnectDiagonally(x, y);
				
			}
		}
	}

	//-------------------------------------------------------------------------------------------
	void ConnectOrthogonally(const int x, const int y)
	{
		if (y > 0)
		{
			Nodes[y * MapWidth + x].Neighbors.push_back(&Nodes[(y - 1) * MapWidth + (x + 0)]);
		}
		if (y < MapHeight - 1)
		{
			Nodes[y * MapWidth + x].Neighbors.push_back(&Nodes[(y + 1) * MapWidth + (x + 0)]);
		}
		if (x > 0)
		{
			Nodes[y * MapWidth + x].Neighbors.push_back(&Nodes[(y + 0) * MapWidth + (x - 1)]);
		}
		if (x < MapWidth - 1)
		{
			Nodes[y * MapWidth + x].Neighbors.push_back(&Nodes[(y + 0) * MapWidth + (x + 1)]);
		}
	}

	//-------------------------------------------------------------------------------------------
	void ConnectDiagonally(const int x, const int y)
	{
		if (y > 0 && x > 0)
		{
			Nodes[y * MapWidth + x].Neighbors.push_back(&Nodes[(y - 1) * MapWidth + (x - 1)]);
		}
		if (y < MapHeight - 1 && x > 0)
		{
			Nodes[y * MapWidth + x].Neighbors.push_back(&Nodes[(y + 1) * MapWidth + (x - 1)]);
		}
		if (y > 0 && x < MapWidth - 1)
		{
			Nodes[y * MapWidth + x].Neighbors.push_back(&Nodes[(y - 1) * MapWidth + (x + 1)]);
		}
		if (y < MapHeight - 1 && x < MapWidth - 1)
		{
			Nodes[y * MapWidth + x].Neighbors.push_back(&Nodes[(y + 1) * MapWidth + (x + 1)]);
		}
	}

	//-------------------------------------------------------------------------------------------
	void UpdateGridStates()
	{
		//Use integer division to nicely get cursor position in node space
		int SelectedNodeX = GetMouseX() / NodeSize;
		int SelectedNodeY = GetMouseY() / NodeSize;

		if (GetMouse(0).bReleased) //Use mouse to draw maze, shift and ctrl to place start and end
		{
			if (SelectedNodeX >= 0 && SelectedNodeX < MapWidth)
			{
				if (SelectedNodeY >= 0 && SelectedNodeY < MapHeight)
				{
					if (GetKey(olc::Key::SHIFT).bHeld)
					{
						StartNode = &Nodes[SelectedNodeY * MapWidth + SelectedNodeX];
					}
					else if (GetKey(olc::Key::CTRL).bHeld)
					{
						EndNode = &Nodes[SelectedNodeY * MapWidth + SelectedNodeX];
					}
					else
					{
						Nodes[SelectedNodeY * MapWidth + SelectedNodeX].bObstacle = !Nodes[SelectedNodeY * MapWidth + SelectedNodeX].bObstacle;
					}

					SolveAStar();

				}
			}
		}
	}

	//-------------------------------------------------------------------------------------------
	void SolveAStar()
	{
		//Reset Navigation Graph - default all node states
		ResetNavGraph();

		//Lambda Functions, for convenience
		auto Distance = [](FNode* a, FNode* b) 
		{
			return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
		};

		auto Heuristic = [Distance](FNode* a, FNode* b)
		{
			return Distance(a, b);
		};

		//Setup starting conditions
		FNode* Current = StartNode;
		StartNode->LocalGoal = 0.0f;
		StartNode->GlobalGoal = Heuristic(StartNode, EndNode);

		// Add Start Node to not tested list - this will ensure it gets tested.
		// As the algorithm progresses, newly discovered nodes get added to the list, and will themselves be tested later.
		std::list<FNode*> NotTested;
		NotTested.push_back(StartNode);

		while (!NotTested.empty() && Current != EndNode)
		{
			//Sort untested nodes by global goal
			NotTested.sort([](const FNode* LeftHandSide, const FNode* RightHandSide) { return LeftHandSide->GlobalGoal < RightHandSide->GlobalGoal; });

			//Front of list is potentially the lowest distance node
			// List may also contain nodes that have been visited, so ditch these
			while (!NotTested.empty() && NotTested.front()->bVisited)
			{
				NotTested.pop_front();
			}

			//Abort if no valid nodes left to test
			if (NotTested.empty())
			{
				break;
			}

			Current = NotTested.front();
			Current->bVisited = true; // We only explore a node once

			//Check each of this node's neighbours...
			for (auto Neighbor : Current->Neighbors)
			{
				// ... and only if the neighbour is not visited and is not an obstacle, add it to the NotTested List
				if (!Neighbor->bVisited && !Neighbor->bObstacle)
				{
					NotTested.push_back(Neighbor);
				}

				//Calculate the neighbours potential lowest parent distance
				float PossiblyLowerGoal = Current->LocalGoal + Distance(Current, Neighbor);

				//If choosing to path through this node is a lower distance than what the neighbour currently has set,
				// update the neighbour to use this node as the path source, and set its distance scores as necessary
				if (PossiblyLowerGoal < Neighbor->LocalGoal)
				{
					Neighbor->Parent = Current;
					Neighbor->LocalGoal = PossiblyLowerGoal;

					//The best path length to the neighbour being tested has changed, so update the neighbour's score.
					//The heuristic is used to globally bias the path algorithm, so it knows if its getting better or worse.
					//At some point, the algorithm will realize this path is worse and abandon it, and then go and search along the next best path.
					Neighbor->GlobalGoal = Neighbor->LocalGoal + Heuristic(Neighbor, EndNode);
				}

			}

		}
	}

	//-------------------------------------------------------------------------------------------
	void ResetNavGraph()
	{
		for (int x = 0; x < MapWidth; x++)
		{
			for (int y = 0; y < MapHeight; y++)
			{
				Nodes[y * MapWidth + x].bVisited = false;
				Nodes[y * MapWidth + x].GlobalGoal = INFINITY;
				Nodes[y * MapWidth + x].LocalGoal = INFINITY;
				Nodes[y * MapWidth + x].Parent = nullptr; // No parent
			}
		}
	}

	//-------------------------------------------------------------------------------------------
	void DrawConnections()
	{
		for (int x = 0; x < MapWidth; x++)
		{
			for (int y = 0; y < MapHeight; y++)
			{
				for (auto n : Nodes[y * MapWidth + x].Neighbors)
				{
					DrawLine(x * NodeSize + NodeSize / 2, y * NodeSize + NodeSize / 2, n->x * NodeSize + NodeSize / 2, n->y * NodeSize + NodeSize / 2, olc::DARK_BLUE);
				}
			}
		}
	}

	//-------------------------------------------------------------------------------------------
	void DrawNodes()
	{
		for (int x = 0; x < MapWidth; x++)
		{
			for (int y = 0; y < MapHeight; y++)
			{
				FillRect(x * NodeSize + NodeBorder, y * NodeSize + NodeBorder, NodeInner, NodeInner, Nodes[y * MapWidth + x].bObstacle ? olc::GREY : olc::DARK_BLUE);

				if (Nodes[y * MapWidth + x].bVisited)
				{
					FillRect(x * NodeSize + NodeBorder, y * NodeSize + NodeBorder, NodeInner, NodeInner, olc::BLUE);
				}

				if (&Nodes[y * MapWidth + x] == StartNode)
				{
					FillRect(x * NodeSize + NodeBorder, y * NodeSize + NodeBorder, NodeInner, NodeInner, olc::GREEN);
				}

				if (&Nodes[y * MapWidth + x] == EndNode)
				{
					FillRect(x * NodeSize + NodeBorder, y * NodeSize + NodeBorder, NodeInner, NodeInner, olc::RED);
				}
			}
		}
	}

	//-------------------------------------------------------------------------------------------
	void DrawPath()
	{
		if (EndNode)
		{
			FNode* Current = EndNode;
			while (Current->Parent)
			{
				DrawLine(Current->x * NodeSize + NodeSize / 2, Current->y * NodeSize + NodeSize / 2, Current->Parent->x * NodeSize + NodeSize / 2, Current->Parent->y * NodeSize + NodeSize / 2, olc::YELLOW);


				//Set next node to this node's parent
				Current = Current->Parent;
			}
		}
	}

};

int main()
{
	FPathfinding demo;
	if (demo.Construct(144, 144, 6, 6))
		demo.Start();
	return 0;
}