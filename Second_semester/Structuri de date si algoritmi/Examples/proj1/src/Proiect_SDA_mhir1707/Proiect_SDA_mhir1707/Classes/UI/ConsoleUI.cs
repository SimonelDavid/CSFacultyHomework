using System;
using System.Collections.Generic;

using Proiect_SDA_mhir1707.Domain;
using Proiect_SDA_mhir1707.Controller;
using Proiect_SDA_mhir1707.Repository;

namespace Proiect_SDA_mhir1707.UI
{
    public class ConsoleUI
    {
        ParticipantController controller;

        public ConsoleUI(ParticipantController controller)
        {
            this.controller = controller;
        }

        private void CreateParticipant()
        {
            string id = "", name = "";
            int age = 0;
            float score = 0;
            string input;

            input = string.Empty;
            while (input == string.Empty)
            {
                Console.Write("ID = ");
                input = Console.ReadLine();
                if (input != string.Empty)
                    id = input;
            }

            input = string.Empty;
            while (input == string.Empty)
            {
                Console.Write("Name = ");
                input = Console.ReadLine();

                if (input != string.Empty)
                    name = input;
            }

            input = string.Empty;
            while (input == string.Empty)
            {
                Console.Write("Age = ");
                input = Console.ReadLine();

                if (input != string.Empty)
                    age = int.Parse(input);
            }

            input = string.Empty;
            while (input == string.Empty)
            {
                Console.Write("Score = ");
                input = Console.ReadLine();

                if (input != string.Empty)
                    score = float.Parse(input);
            }

            try
            {
                controller.CreateParticipant(id, name, age, score);
            }
            catch (ParticipantValidatorException ex)
            {
                Console.WriteLine(ex.Message);
            }
            catch (ParticipantRepositoryException ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private void RemoveParticipant()
        {
            string id;

            Console.Write("ID = ");
            id = Console.ReadLine();

            try
            {
                controller.RemoveParticipant(id);
            }
            catch (ParticipantRepositoryException ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private void RemoveAllParticipants()
        {
            controller.RemoveAllParticipants();
        }

        private void ListParticipants()
        {
            List<Participant> all = controller.GetAllParticipants();

            foreach (Participant par in all)
                Console.WriteLine(par);

            if (all.Count == 0)
                Console.WriteLine("There are no participants");
            else
                Console.WriteLine("Total number of participants: " + all.Count);
        }

        private void ListPrizewinners()
        {
            List<Participant> win = controller.GetPrizewinners();

            foreach (Participant par in win)
                Console.WriteLine(par);

            if (win.Count == 0)
                Console.WriteLine("There are no prizewinners");
            else
                Console.WriteLine("Total number of prizewinners: " + win.Count);
        }

        private void ListMentions()
        {
            List<Participant> men = controller.GetMentions();

            foreach (Participant par in men)
                Console.WriteLine(par);

            if (men.Count == 0)
                Console.WriteLine("There are no mentions");
            else
                Console.WriteLine("Total number of mentions: " + men.Count);
        }

        private void GetParticipantScore()
        {
            string id = "";
            string input;

            input = string.Empty;
            while (input == string.Empty)
            {
                Console.Write("ID = ");
                input = Console.ReadLine();
                if (input != string.Empty)
                    id = input;
            }

            try
            {
                Participant par = controller.GetParticipant(id);

                Console.WriteLine(par.Name + "'s score is " + par.Score);
            }
            catch (ParticipantRepositoryException ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private void ModifyParticipant()
        {
            string id = "", name = "";
            int age = 0;
            float score = 0;
            string input;

            input = string.Empty;
            while (input == string.Empty)
            {
                Console.Write("ID = ");
                input = Console.ReadLine();
                if (input != string.Empty)
                    id = input;
            }

            input = string.Empty;
            while (input == string.Empty)
            {
                Console.Write("New Name = ");
                input = Console.ReadLine();

                if (input != string.Empty)
                    name = input;
            }

            input = string.Empty;
            while (input == string.Empty)
            {
                Console.Write("New Age = ");
                input = Console.ReadLine();

                if (input != string.Empty)
                    age = int.Parse(input);
            }

            input = string.Empty;
            while (input == string.Empty)
            {
                Console.Write("New Score = ");
                input = Console.ReadLine();

                if (input != string.Empty)
                    score = float.Parse(input);
            }

            try
            {
                controller.RemoveParticipant(id);
                controller.CreateParticipant(id, name, age, score);
            }
            catch (ParticipantValidatorException ex)
            {
                Console.WriteLine(ex.Message);
            }
            catch (ParticipantRepositoryException ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private void PrintMenu()
        {
            Console.WriteLine("=== MAIN MENU ===");
            Console.WriteLine("1. Create participant");
            Console.WriteLine("2. Remove participant");
            Console.WriteLine("3. Remove all participants");
            Console.WriteLine("4. List participants");
            Console.WriteLine("5. List prizewinners");
            Console.WriteLine("6. List mentions");
            Console.WriteLine("7. Get score");
            Console.WriteLine("8. Modify a participant");
            Console.WriteLine("0. EXIT");
        }

        public void Show()
        {
            while (true)
            {
                PrintMenu();
                string cmd;

                Console.Write("Your choice = ");
                cmd = Console.ReadLine();

                switch (cmd)
                {
                    case "0":
                        return;

                    case "1":
                        CreateParticipant();
                        break;

                    case "2":
                        RemoveParticipant();
                        break;

                    case "3":
                        RemoveAllParticipants();
                        break;

                    case "4":
                        ListParticipants();
                        break;

                    case "5":
                        ListPrizewinners();
                        break;

                    case "6":
                        ListMentions();
                        break;

                    case "7":
                        GetParticipantScore();
                        break;

                    case "8":
                        ModifyParticipant();
                        break;
                }

                Console.WriteLine();
            }
        }
    }
}

