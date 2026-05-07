add_executable(01_MatrixGraph 01_MatrixGraph/main.c
		01_MatrixGraph/matrixGraph.c 01_MatrixGraph/matrixGraph.h)

add_executable(02_AdjacencyList 02_AdjacencyList/main.c
		02_AdjacencyList/adjacencyList.c 02_AdjacencyList/adjacencyList.h)

add_executable(03_CrossLinkedGraph 03_CrossLinkedGraph/main.c
		03_CrossLinkedGraph/crossLinkGraph.c 03_CrossLinkedGraph/crossLinkGraph.h)

add_executable(04_AdjacencyMultiList 04_AdjacencyMultiList/main.c
		04_AdjacencyMultiList/adjacencyMultiList.c 04_AdjacencyMultiList/adjacencyMultiList.h)

add_executable(05_MiniTree 05_MiniTree/main.c
		05_MiniTree/Kruskal.c 05_MiniTree/Kruskal.h
		01_MatrixGraph/matrixGraph.c 01_MatrixGraph/matrixGraph.h
		05_MiniTree/common.h
		05_MiniTree/Prim.c
		05_MiniTree/Prim.h)

add_executable(06_ShortPath 06_ShortPath/main.c
		06_ShortPath/DijkstraShortPath.c 06_ShortPath/DijkstraShortPath.h
		01_MatrixGraph/matrixGraph.c 01_MatrixGraph/matrixGraph.h)
