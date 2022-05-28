using System;
using System.Collections.Generic;

using Proiect_SDA_mhir1707.Domain;
using Proiect_SDA_mhir1707.Repository;

namespace Proiect_SDA_mhir1707.Controller
{
    public class ParticipantController
    {
        ParticipantRepository repository;
        ParticipantValidator validator;

        public ParticipantController(ParticipantRepository repository, ParticipantValidator validator)
        {
            this.repository = repository;
            this.validator = validator;
        }

        public void CreateParticipant(string id, string name, int age, float score)
        {
            Participant par = new Participant(id, name, age, score);
            validator.Validate(par);
            repository.Store(par);
        }

        public void RemoveParticipant(string id)
        {
            repository.Remove(id);
        }

        public void RemoveAllParticipants()
        {
            repository.Clear();
        }

        public int ParticipantsCount
        {
            get
            {
                return repository.Size;
            }
        }

        public bool ParticipantExists(string id)
        {
            return repository.Contains(id);
        }

        public Participant GetParticipant(string id)
        {
            return repository.Get(id);
        }

        public List<Participant> GetAllParticipants()
        {
            return repository.GetAll();
        }

        public List<Participant> GetPrizewinners()
        {
            List<Participant> all = repository.GetAll();
            List<Participant> win = new List<Participant>();
            int remaining = 3;

            all.Reverse();

            foreach (Participant par in all)
            {
                if (par.Score >= 60)
                {
                    win.Add(par);
                    remaining -= 1;
                }
                else
                    break;

                if (remaining == 0)
                    break;
            }

            return win;
        }

        public List<Participant> GetMentions()
        {
            List<Participant> all = repository.GetAll();
            List<Participant> win = GetPrizewinners();
            List<Participant> men = new List<Participant>();
            int remaining = (int)(repository.Size * 0.25) - win.Count;

            all.Reverse();

            foreach (Participant par in all)
                if (win.Contains(par) == false)
                {
                    if (par.Score >= 40)
                    {
                        men.Add(par);
                        remaining -= 1;
                    }
                    else
                        break;

                    if (remaining == 0)
                        break;
                }

            return men;
        }
    }
}
