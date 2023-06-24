using System.Data;
using Microsoft.Data.SqlClient;
namespace pb1Practic
{
    public partial class Form1 : Form
    {
        string connectionString = "Server=DESKTOP-VCR5GTN\\SQLEXPRESS;Database=Problema3;Integrated Security=true;TrustServerCertificate=true;";
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
                    parentAdapter.SelectCommand = new SqlCommand("Select * From Producatori;", conn);
                    childAdapter.SelectCommand = new SqlCommand("Select * From Biscuiti;", conn);
                    parentAdapter.Fill(ds, "Producatori");
                    childAdapter.Fill(ds, "Biscuiti");
                    parentBS.DataSource = ds.Tables["Producatori"];
                    dataGridViewParent.DataSource = parentBS;
                    DataColumn parentColumn = ds.Tables["Producatori"].Columns["cod_p"];
                    DataColumn childColumn = ds.Tables["Biscuiti"].Columns["cod_p"];
                    DataRelation relation = new DataRelation("FK_Relation", parentColumn, childColumn);
                    ds.Relations.Add(relation);
                    childBS.DataSource = parentBS;
                    childBS.DataMember = "FK_Relation";
                    dataGridViewChild.DataSource = childBS;
                    textBoxNume.DataBindings.Add("Text", childBS, "nume_b");
                    textBoxDescriere.DataBindings.Add("Text", childBS, "nr_calorii");
                    textBoxPret.DataBindings.Add("Text", childBS, "pret");
                    textBoxCod.DataBindings.Add("Text", childBS, "cod_p");
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
                    string addQuery = "Insert Into Biscuiti(nume_b,nr_calorii,pret,cod_p) Values (@nume,@nr_calorii,@pret,@cod);";
                    SqlCommand cmd = new SqlCommand(addQuery, conn);
                    cmd.Parameters.AddWithValue("@nume", textBoxNume.Text);
                    cmd.Parameters.AddWithValue("@nr_calorii", textBoxDescriere.Text);
                    cmd.Parameters.AddWithValue("@pret", textBoxPret.Text);
                    cmd.Parameters.AddWithValue("@cod", textBoxCod.Text);
                    childAdapter.InsertCommand = cmd;
                    childAdapter.SelectCommand.Connection = conn;

                    childAdapter.InsertCommand.ExecuteNonQuery();

                    if (ds.Tables.Contains("Biscuiti"))
                        ds.Tables["Biscuiti"].Clear();
                    childAdapter.Fill(ds, "Biscuiti");

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
                    string updateQuery = "Update Biscuiti SET nume_b = @nume, nr_calorii=@nr_calorii,pret=@pret WHERE cod_b=@cod;";

                    SqlCommand cmd = new SqlCommand(updateQuery, conn);
                    cmd.Parameters.AddWithValue("@nume", textBoxNume.Text);
                    cmd.Parameters.AddWithValue("@nr_calorii", textBoxDescriere.Text);
                    cmd.Parameters.AddWithValue("@pret", textBoxPret.Text);
                    cmd.Parameters.AddWithValue("@cod", dataGridViewChild.CurrentRow.Cells["cod_b"].Value.ToString());
                    childAdapter.UpdateCommand = cmd;
                    childAdapter.SelectCommand.Connection = conn;

                    childAdapter.UpdateCommand.ExecuteNonQuery();

                    if (ds.Tables.Contains("Biscuiti"))
                        ds.Tables["Biscuiti"].Clear();
                    childAdapter.Fill(ds, "Biscuiti");

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
                    string deleteQuery = "Delete From Biscuiti Where cod_b = @cod";
                    SqlCommand cmd = new SqlCommand(deleteQuery, conn);
                    cmd.Parameters.AddWithValue("cod", dataGridViewChild.CurrentRow.Cells["cod_b"].Value.ToString());
                    childAdapter.DeleteCommand = cmd;
                    childAdapter.SelectCommand.Connection = conn;

                    childAdapter.DeleteCommand.ExecuteNonQuery();

                    if (ds.Tables.Contains("Biscuiti"))
                        ds.Tables["Biscuiti"].Clear();
                    childAdapter.Fill(ds, "Biscuiti");
                }

            }catch (Exception ex) {
                MessageBox.Show(ex.Message);
            }
        }
    }
}