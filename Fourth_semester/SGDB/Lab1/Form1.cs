using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Project1_SGBD
{
    public partial class Form1 : Form
    {
        SqlConnection cs = new SqlConnection("Data Source = DESKTOP-VCR5GTN\\SQLEXPRESS;" +
            " Initial Catalog = Bolt_Food; Integrated Security = True");
        SqlDataAdapter da = new SqlDataAdapter();
        BindingSource bsP = new BindingSource();
        BindingSource bsC = new BindingSource();
        DataSet dsP = new DataSet();
        DataSet dsC = new DataSet();
        public Form1()
        {
            InitializeComponent();
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            da.SelectCommand = new SqlCommand("SELECT * FROM Meniu", cs);
            dsP.Clear();
            da.Fill(dsP);
            dataGridViewParent.DataSource = dsP.Tables[0];
            bsP.DataSource = dsP.Tables[0];
            //txtFirstName.DataBindings.Add("Text", bs, "FirstName");
            //txtLastName.DataBindings.Add("Text", bs, "LastName");
            // Conection between texbox and the record from the Binding Source
            //last parameter is the name of the field of the table.
            // always will be inserted the first line in the TextBox-es
            // to move to next rows or others, can be use the methods MoveFirst(), MoveNext(), MovePrevious(),
            bsP.MoveLast();
            // there is no need to populate the Text Box-es for each method, because it works automattically
        }

        private void dataGridViewParent_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (dataGridViewParent.Rows[e.RowIndex].Cells[e.ColumnIndex].Value == null)
                return;


            string Id_Meniu = dataGridViewParent.Rows[e.RowIndex].Cells[0].Value.ToString();


            //Fel_De_Mancare
            
            da.SelectCommand = new SqlCommand("SELECT * from Fel_De_Mancare " +
                    "where Fel_De_Mancare.Id_Meniu = " + Id_Meniu + "; ", cs);
            dsC.Clear();
            da.Fill(dsC);
            dataGridViewChild.DataSource = dsC.Tables[0];
            bsC.DataSource = dsC.Tables[0];
        }

        private void dataGridViewChild_CellEndEdit(object sender, DataGridViewCellEventArgs e)
        {
            /*int x;
            da.UpdateCommand = new SqlCommand("Update Contacts set" +
                " FIRSTNAME = @f, LASTNAME = @l where" +
                "ID = @id", cs);
           
            da.UpdateCommand.Parameters.Add("@f",
            SqlDbType.VarChar).Value = txtFirstName.Text;
            da.UpdateCommand.Parameters.Add("@l",
            SqlDbType.VarChar).Value = txtLastName.Text;
            da.UpdateCommand.Parameters.Add("@id",
            SqlDbType.Int).Value = ds.Tables[0].Rows[bs.Position][0];

            cs.Open();
            x = da.UpdateCommand.ExecuteNonQuery();
            cs.Close();
            if (x >= 1)
            {
                MessageBox.Show("The record has been updated"); 
            }*/
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            if (dataGridViewParent.SelectedCells.Count == 0)
            {
                MessageBox.Show("O linie in parinte trebuie slectata!");
                return;
            }
            else if(dataGridViewParent.SelectedCells.Count > 1)
            {
                MessageBox.Show("O singura linie in parinte trebuie slectata!");
                return;
            }

            try
            {
                float.Parse(textBoxPret.Text);
            }
            catch(Exception exception)
            {
                MessageBox.Show("Pretul trebuie sa fie un numar!", exception.Message);
                return;
            }

            try
            {
                float.Parse(textBoxCantitate.Text);
            }
            catch (Exception exception)
            {
                MessageBox.Show("Cantitatea trebuie sa fie un numar!", exception.Message);
                return;
            }

            da.InsertCommand = new
                SqlCommand("INSERT INTO Fel_De_Mancare(Id_Meniu, Cantitate, Denumire, Pret, Descriere)" +
                    " VALUES (@id,@C,@D,@P,@Descriere);", cs);
            da.InsertCommand.Parameters.Add("@id",
                SqlDbType.Int).Value = dsP.Tables[dataGridViewParent.CurrentCell.ColumnIndex].Rows[dataGridViewParent.CurrentCell.RowIndex][0];

            da.InsertCommand.Parameters.Add("@C",
                SqlDbType.Float).Value = float.Parse(textBoxCantitate.Text);

            da.InsertCommand.Parameters.Add("@D",
                SqlDbType.VarChar).Value = textBoxDenumire.Text;

            da.InsertCommand.Parameters.Add("@P",
                SqlDbType.Float).Value = float.Parse(textBoxPret.Text);

            da.InsertCommand.Parameters.Add("@Descriere",
                SqlDbType.VarChar).Value = textBoxDescriere.Text;

            cs.Open();
            da.InsertCommand.ExecuteNonQuery();
            cs.Close();
            dsC.Clear();
            da.Fill(dsC);
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            if (dataGridViewChild.SelectedCells.Count == 0)
            {
                MessageBox.Show("O linie in copil trebuie slectata!");
                return;
            }
            else if (dataGridViewChild.SelectedCells.Count > 1)
            {
                MessageBox.Show("O singura linie in copil trebuie slectata!");
                return;
            }

            da.DeleteCommand = new SqlCommand("Delete " +
            "from Fel_De_Mancare where Id_Mancare = @id;", cs);

            da.DeleteCommand.Parameters.Add("@id",
                SqlDbType.Int).Value = dsC.Tables[0].Rows[dataGridViewChild.CurrentCell.RowIndex][0];

            cs.Open();
            da.DeleteCommand.ExecuteNonQuery();
            cs.Close();
            dsC.Clear();
            da.Fill(dsC);
        }
        private void buttonUpdate_Click(object sender, EventArgs e)
        {
            if (dataGridViewChild.SelectedCells.Count == 0)
            {
                MessageBox.Show("O linie in copil trebuie slectata!");
                return;
            }
            else if (dataGridViewChild.SelectedCells.Count > 1)
            {
                MessageBox.Show("O singura linie in copil trebuie slectata!");
                return;
            }

            try
            {
                float.Parse(textBoxPret.Text);
            }
            catch (Exception exception)
            {
                MessageBox.Show("Pretul trebuie sa fie un numar!", exception.Message);
                return;
            }

            try
            {
                float.Parse(textBoxCantitate.Text);
            }
            catch (Exception exception)
            {
                MessageBox.Show("Cantitatea trebuie sa fie un numar!", exception.Message);
                return;
            }

            int x;
            da.UpdateCommand = new SqlCommand("Update " +
                "Fel_De_Mancare set Cantitate = @C, Denumire = @D," +
                " Pret = @P, Descriere = @Descriere " +
                "where Id_Mancare=@id", cs);

            da.UpdateCommand.Parameters.Add("@id",
                SqlDbType.Int).Value = dsC.Tables[0].Rows[dataGridViewChild.CurrentCell.RowIndex][0];
       
            da.UpdateCommand.Parameters.Add("@C",
                SqlDbType.Float).Value = float.Parse(textBoxCantitate.Text);

            da.UpdateCommand.Parameters.Add("@D",
                SqlDbType.VarChar).Value = textBoxDenumire.Text;

            da.UpdateCommand.Parameters.Add("@P",
                SqlDbType.Float).Value = float.Parse(textBoxPret.Text);

            da.UpdateCommand.Parameters.Add("@Descriere",
                SqlDbType.VarChar).Value = textBoxDescriere.Text;


            cs.Open();
            x = da.UpdateCommand.ExecuteNonQuery();
            cs.Close();
            dsC.Clear();
            da.Fill(dsC);

            if (x >= 1)
                MessageBox.Show("The record has been updated");
        }
    }
}