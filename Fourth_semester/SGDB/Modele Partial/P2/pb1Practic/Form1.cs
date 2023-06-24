using System.Data;
using Microsoft.Data.SqlClient;
namespace pb1Practic
{
    public partial class Form1 : Form
    {
        string connectionString = "Server=DESKTOP-VCR5GTN\\SQLEXPRESS;Database=Problema2;Integrated Security=true;TrustServerCertificate=true;";
        DataSet ds = new DataSet();
        SqlDataAdapter parentAdapter = new SqlDataAdapter();
        SqlDataAdapter childAdapter = new SqlDataAdapter();
        BindingSource parentBS = new BindingSource();
        BindingSource childBS = new BindingSource();
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(connectionString))
                {
                    conn.Open();
                    parentAdapter.SelectCommand = new SqlCommand("Select * From Artisti;", conn);
                    childAdapter.SelectCommand = new SqlCommand("Select * From Melodii;", conn);
                    parentAdapter.Fill(ds, "Artisti");
                    childAdapter.Fill(ds, "Melodii");
                    parentBS.DataSource = ds.Tables["Artisti"];
                    dataGridViewParent.DataSource = parentBS;
                    DataColumn parentColumn = ds.Tables["Artisti"].Columns["cod_artist"];
                    DataColumn childColumn = ds.Tables["Melodii"].Columns["cod_artist"];
                    DataRelation relation = new DataRelation("FK_Relation", parentColumn, childColumn);
                    ds.Relations.Add(relation);
                    childBS.DataSource = parentBS;
                    childBS.DataMember = "FK_Relation";
                    dataGridViewChild.DataSource = childBS;
                    textBoxNume.DataBindings.Add("Text", childBS, "titlu");
                    textBoxDescriere.DataBindings.Add("Text", childBS, "durata");
                    textBoxPret.DataBindings.Add("Text", childBS, "an_lansare");
                    textBoxCod.DataBindings.Add("Text", childBS, "cod_artist");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(connectionString))
                {
                    conn.Open();
                    string addQuery = "Insert Into Melodii(titlu,durata,an_lansare,cod_artist) Values (@nume,@durata,@an_lansare,@cod);";
                    SqlCommand cmd = new SqlCommand(addQuery, conn);
                    cmd.Parameters.AddWithValue("@nume", textBoxNume.Text);
                    cmd.Parameters.AddWithValue("@durata", textBoxDescriere.Text);
                    cmd.Parameters.AddWithValue("@an_lansare", textBoxPret.Text);
                    cmd.Parameters.AddWithValue("@cod", textBoxCod.Text);
                    childAdapter.InsertCommand = cmd;
                    childAdapter.SelectCommand.Connection = conn;

                    childAdapter.InsertCommand.ExecuteNonQuery();

                    if (ds.Tables.Contains("Melodii"))
                        ds.Tables["Melodii"].Clear();
                    childAdapter.Fill(ds, "Melodii");

                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void buttonModifica_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(connectionString))
                {
                    conn.Open();
                    string updateQuery = "Update Melodii SET titlu = @nume, durata=@durata,an_lansare=@an_lansare WHERE cod_briosa=@cod;";

                    SqlCommand cmd = new SqlCommand(updateQuery, conn);
                    cmd.Parameters.AddWithValue("@nume", textBoxNume.Text);
                    cmd.Parameters.AddWithValue("@durata", textBoxDescriere.Text);
                    cmd.Parameters.AddWithValue("@an_lansare", textBoxPret.Text);
                    cmd.Parameters.AddWithValue("@cod", dataGridViewChild.CurrentRow.Cells["cod_briosa"].Value.ToString());
                    childAdapter.UpdateCommand = cmd;
                    childAdapter.SelectCommand.Connection = conn;

                    childAdapter.UpdateCommand.ExecuteNonQuery();

                    if (ds.Tables.Contains("Melodii"))
                        ds.Tables["Melodii"].Clear();
                    childAdapter.Fill(ds, "Melodii");

                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void buttonSterge_Click(object sender, EventArgs e)
        {
            try
            {
                using(SqlConnection conn = new SqlConnection(connectionString))
                {
                    conn.Open();
                    string deleteQuery = "Delete From Melodii Where cod_briosa = @cod";
                    SqlCommand cmd = new SqlCommand(deleteQuery, conn);
                    cmd.Parameters.AddWithValue("cod", dataGridViewChild.CurrentRow.Cells["cod_briosa"].Value.ToString());
                    childAdapter.DeleteCommand = cmd;
                    childAdapter.SelectCommand.Connection = conn;

                    childAdapter.DeleteCommand.ExecuteNonQuery();

                    if (ds.Tables.Contains("Melodii"))
                        ds.Tables["Melodii"].Clear();
                    childAdapter.Fill(ds, "Melodii");
                }

            }catch (Exception ex) {
                MessageBox.Show(ex.Message);
            }
        }
    }
}