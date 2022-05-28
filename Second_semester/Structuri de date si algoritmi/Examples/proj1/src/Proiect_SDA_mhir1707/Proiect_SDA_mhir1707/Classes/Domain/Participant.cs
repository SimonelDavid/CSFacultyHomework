using System;

namespace Proiect_SDA_mhir1707.Domain
{
    public class Participant : IComparable<Participant>
    {
        string id;
        string name;
        int age;
        float score;

        public string ID
        {
            get
            {
                return id;
            }
        }

        public string Name
        {
            get
            {
                return name;
            }
        }

        public int Age
        {
            get
            {
                return age;
            }
        }

        public float Score
        {
            get
            {
                return score;
            }
        }

        public Participant(string id, string name, int age, float score = 0)
        {
            this.id = id;
            this.name = name;
            this.age = age;
            this.score = score;
        }
            
        /*
        public static bool operator ==(Participant p1, Participant p2)
        {
            return p1.ID == p2.ID;
        }
        public static bool operator ==(Participant p1, string id2)
        {
            return p1.ID == id2;
        }

        public static bool operator !=(Participant p1, Participant p2)
        {
            return p1.ID != p2.ID;
        }
        public static bool operator !=(Participant p1, string id2)
        {
            return p1.id != id2;
        }

        public static bool operator <(Participant p1, Participant p2)
        {
            return p1.score < p2.score;
        }
        public static bool operator >(Participant p1, Participant p2)
        {
            return p1.score > p2.score;
        }
        */

        public override bool Equals(object obj)
        {
            if (obj.GetType() != typeof(Participant))
                return base.Equals(obj);

            Participant other = (Participant)obj;
            return this == other;
        }

        public int CompareTo(Participant other)
        {
            if (other == null)
                return 1;
            else
                return score.CompareTo(other.score);
        }

        public override string ToString() 
        {
            return id + ": " + name + ", " + age + ", " + score;
        }
    }
}

