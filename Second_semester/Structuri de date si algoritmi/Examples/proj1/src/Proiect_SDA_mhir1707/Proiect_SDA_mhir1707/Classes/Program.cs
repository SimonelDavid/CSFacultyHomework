using System;
using System.Diagnostics;

using Proiect_SDA_mhir1707.Repository;
using Proiect_SDA_mhir1707.Controller;
using Proiect_SDA_mhir1707.Domain;
using Proiect_SDA_mhir1707.UI;

namespace Proiect_SDA_mhir1707
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            //ParticipantRepository repository = new ParticipantRepository();
            ParticipantRepositoryFile repository = new ParticipantRepositoryFile("repo_file.csv");
            ParticipantValidator validator = new ParticipantValidator();
            ParticipantController controller = new ParticipantController(repository, validator);
            ConsoleUI ui = new ConsoleUI(controller);

            ui.Show();
        }
    }
}
