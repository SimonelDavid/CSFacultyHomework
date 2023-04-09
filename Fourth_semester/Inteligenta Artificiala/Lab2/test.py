from main import *

def test_dolphins():
    current_directory =  os.getcwd()
    file_path = os.path.join(current_directory, '/Users/simoneldavid/Documents/CSFacultyHomework/Fourth_semester/Inteligenta Artificiala/Lab2/real/dolphins', 'dolphins.gml')
    Graph = nx.read_gml(file_path, label='id')
    copy_of_graph = Graph.copy()
    plotNetwork(copy_of_graph, greedyCommunitiesDetectionByTool(Graph, 2))

def test_football():
    current_directory =  os.getcwd()
    file_path = os.path.join(current_directory,  '/Users/simoneldavid/Documents/CSFacultyHomework/Fourth_semester/Inteligenta Artificiala/Lab2/real/football', 'football.gml')
    Graph = nx.read_gml(file_path, label='id')
    copy_of_graph = Graph.copy()
    plotNetwork(copy_of_graph, greedyCommunitiesDetectionByTool(Graph, 12))

def test_karate():
    current_directory =  os.getcwd()
    file_path = os.path.join(current_directory,  '/Users/simoneldavid/Documents/CSFacultyHomework/Fourth_semester/Inteligenta Artificiala/Lab2/real/karate', 'karate.gml')
    Graph = nx.read_gml(file_path, label='id')
    copy_of_graph = Graph.copy()
    plotNetwork(copy_of_graph, greedyCommunitiesDetectionByTool(Graph, 2))

def test_krebs():
    current_directory =  os.getcwd()
    file_path = os.path.join(current_directory,  '/Users/simoneldavid/Documents/CSFacultyHomework/Fourth_semester/Inteligenta Artificiala/Lab2/real/krebs', 'krebs.gml')
    Graph = nx.read_gml(file_path, label='id')
    copy_of_graph = Graph.copy()
    plotNetwork(copy_of_graph, greedyCommunitiesDetectionByTool(Graph, 3))   

def test_netscience():
    current_directory =  os.getcwd()
    file_path = os.path.join(current_directory,  '/Users/simoneldavid/Documents/CSFacultyHomework/Fourth_semester/Inteligenta Artificiala/Lab2/real/netscience', 'netscience.gml')
    Graph = nx.read_gml(file_path, label='id')
    copy_of_graph = Graph.copy()
    plotNetwork(copy_of_graph, greedyCommunitiesDetectionByTool(Graph, 900)) 

def test_polbooks():
    current_directory =  os.getcwd()
    file_path = os.path.join(current_directory,  '/Users/simoneldavid/Documents/CSFacultyHomework/Fourth_semester/Inteligenta Artificiala/Lab2/real/polbooks', 'polbooks.gml')
    Graph = nx.read_gml(file_path, label='id')
    copy_of_graph = Graph.copy()
    plotNetwork(copy_of_graph, greedyCommunitiesDetectionByTool(Graph, 4))      

def test_adjnoun():
    current_directory =  os.getcwd()
    file_path = os.path.join(current_directory,  '/Users/simoneldavid/Documents/CSFacultyHomework/Fourth_semester/Inteligenta Artificiala/Lab2/real/adjnoun', 'adjnoun.gml')
    Graph = nx.read_gml(file_path, label='id')
    copy_of_graph = Graph.copy()
    plotNetwork(copy_of_graph, greedyCommunitiesDetectionByTool(Graph, 2))  

def test_lesmis():
    current_directory =  os.getcwd()
    file_path = os.path.join(current_directory,  '/Users/simoneldavid/Documents/CSFacultyHomework/Fourth_semester/Inteligenta Artificiala/Lab2/real/lesmis', 'lesmis.gml')
    Graph = nx.read_gml(file_path, label='id')
    copy_of_graph = Graph.copy()
    plotNetwork(copy_of_graph, greedyCommunitiesDetectionByTool(Graph, 3))  

def test_all():
    # testele de la profa
    test_dolphins()
    # test_football()
    # test_karate()
    # test_krebs()

    # teste in plus
    # test_lesmis()     #mizerabilii
    # test_polbooks()   #voturi statele unite
    test_adjnoun()    #cuvinte adiacente
    # test_netscience()   #contributori in network science

if __name__ == '__main__':
    test_all()