class ServicePicturi:

    def __init__(self, repo_picturi):
        self.__repo_picturi = repo_picturi

    def get_repo(self):
        return self.__repo_picturi.get_all()