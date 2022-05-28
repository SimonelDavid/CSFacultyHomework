using System;

namespace Proiect_SDA_mhir1707.Domain
{
    public class ParticipantValidatorException : Exception
    {
        public ParticipantValidatorException (string message) : base (message)
        {
        }

        public ParticipantValidatorException (string[] messages) : base (string.Join(Environment.NewLine, messages))
        {
        }
    }

    public class ParticipantValidator
    {
        public ParticipantValidator()
        {
        }

        public void Validate(Participant p)
        {
            string[] err = new string[3];
            int errs = 0;

            if (p.ID == string.Empty)
            {
                err[errs] = "ID cannot be empty";
                errs += 1;
            }

            if (p.Name == string.Empty)
            {
                err[errs] = "Name cannot be empty";
                errs += 1;
            }

            if (p.Age < 0)
            {
                err[errs] = "Age cannot be negative";
                errs += 1;
            }

            if (errs > 0)
            {
                throw new ParticipantValidatorException(err);
            }
        }
    }
}

