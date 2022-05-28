using System;
using System.Collections.Generic;
using System.IO;

using Proiect_SDA_mhir1707.Domain;
using Proiect_SDA_mhir1707.TAD;

namespace Proiect_SDA_mhir1707.Repository
{
    public class ParticipantRepositoryException : Exception
    {
        public ParticipantRepositoryException(string message) : base (message)
        {
        }
    }

    public class ParticipantRepository
    {
        internal OrderedList<Participant> lst;

        public ParticipantRepository()
        {
            lst = new OrderedList<Participant>();
        }

        public void Clear()
        {
            lst.Clear();
        }

        public virtual void Store(Participant par)
        {
            if (Get(par.ID) != null)
                throw new ParticipantRepositoryException("The specified ID already exists");
            else
                lst.Insert(par);
        }

        public int Size
        {
            get
            {
                return lst.Count;
            }
        }

        public virtual void Remove(string id)
        {
            Participant par = Get(id);
            lst.Remove(par);
        }

        public bool Contains(string id)
        {
            Iterator<Participant> it = lst.CreateIterator();

            while (it.Valid)
            {
                if (it.CurrentElement.ID == id)
                    return true;

                it.Next();
            }

            return false;
        }

        public Participant Get(string id)
        {
            Iterator<Participant> it = lst.CreateIterator();

            while (it.Valid)
            {
                if (it.CurrentElement.ID == id)
                    return it.CurrentElement;

                it.Next();
            }

            throw new ParticipantRepositoryException("The specified ID does not exist");
        }

        public List<Participant> GetAll()
        {
            List<Participant> all = new List<Participant>();
            Iterator<Participant> it = lst.CreateIterator();

            while (it.Valid)
            {
                all.Add(it.CurrentElement);
                it.Next();
            }

            return all;
        }
    }

    public class ParticipantRepositoryFile : ParticipantRepository
    {
        string filePath;

        public ParticipantRepositoryFile(string filePath)
        {
            this.lst = new OrderedList<Participant>();
            this.filePath = filePath;
            ReadAll();
        }

        private void WriteAll()
        {
            StreamWriter sw = new StreamWriter(filePath);
         

            Queue<BSTNode<Participant>> q = new Queue<BSTNode<Participant>>();
            q.Enqueue(lst.root);

            while(q.Count > 0)
            {
                BSTNode<Participant> current = q.Dequeue();

                if(current == null)
                    continue;

                q.Enqueue(current.ChildLeft);
                q.Enqueue(current.ChildRight);

                sw.WriteLine(
                    current.Element.ID + ',' +
                    current.Element.Name + ',' +
                    current.Element.Age + ',' +
                    current.Element.Score);
            }

            sw.Dispose();
        }

        private void ReadAll()
        {
            if (File.Exists(filePath) == false)
                return;
            
            StreamReader sr = new StreamReader(filePath);

            while (sr.EndOfStream == false)
            {
                string line = sr.ReadLine();
                string[] fields = line.Split(',');
                lst.Insert(new Participant(fields[0], fields[1], int.Parse(fields[2]), float.Parse(fields[3])));
            }

            sr.Dispose();
        }

        public override void Store(Participant par)
        {
            base.Store(par);
            WriteAll();
        }

        public override void Remove(string id)
        {
            base.Remove(id);
            WriteAll();
        }
    }
}

