from Domain.melody import Melody
from Repository.Music_file_repo import MusicRepoFile
from Service.MelodyService import MelodyService
from UI.console import UserInterface
from Validation.melodyValidation import MelodyValidation

melodii_repo = MusicRepoFile("melodii.txt")
validare_melodii = MelodyValidation()
melody_service = MelodyService(validare_melodii,melodii_repo)
user_console = UserInterface(melody_service)
user_console.run()