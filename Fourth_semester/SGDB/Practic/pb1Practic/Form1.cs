using System.Data;
using Microsoft.Data.SqlClient;
namespace pb1Practic
{
    public partial class Form1 : Form
    {
        string connectionString = "Server=DESKTOP-VCR5GTN\\SQLEXPRESS;Database=S32023;Integrated Security=true;TrustServerCertificate=true;";
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
                    parentAdapter.SelectCommand = new SqlCommand("Select * From Destinatii;", conn);
                    childAdapter.SelectCommand = new SqlCommand("Select * From Sejururi;", conn);
                    parentAdapter.Fill(ds, "Destinatii");
                    childAdapter.Fill(ds, "Sejururi");
                    parentBS.DataSource = ds.Tables["Destinatii"];
                    dataGridViewParent.DataSource = parentBS;
                    DataColumn parentColumn = ds.Tables["Destinatii"].Columns["cod_d"];
                    DataColumn childColumn = ds.Tables["Sejururi"].Columns["cod_d"];
                    DataRelation relation = new DataRelation("FK_Relation", parentColumn, childColumn);
                    ds.Relations.Add(relation);
                    childBS.DataSource = parentBS;
                    childBS.DataMember = "FK_Relation";
                    dataGridViewChild.DataSource = childBS;
                    textBoxNume.DataBindings.Add("Text", childBS, "nume_sejur");
                    textBoxDetalii.DataBindings.Add("Text", childBS, "detalii_sejur");
                    textBoxDataIncepere.DataBindings.Add("Text", childBS, "data_inceput");
                    textBoxDataSfarsit.DataBindings.Add("Text", childBS, "data_sfarsit");
                    textBoxCod.DataBindings.Add("Text", childBS, "cod_d");
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
                    string addQuery = "Insert Into Sejururi(nume_sejur,detalii_sejur,data_inceput,data_sfarsit,cod_d) Values (@nume,@detalii_sejur,@data_inceput,@data_sfarsit,@cod_d);";
                    SqlCommand cmd = new SqlCommand(addQuery, conn);
                    cmd.Parameters.AddWithValue("@nume", textBoxNume.Text);
                    cmd.Parameters.AddWithValue("@detalii_sejur", textBoxDetalii.Text);
                    cmd.Parameters.AddWithValue("@data_inceput", textBoxDataIncepere.Text);
                    cmd.Parameters.AddWithValue("@data_sfarsit", textBoxDataSfarsit.Text);
                    cmd.Parameters.AddWithValue("@cod_d", textBoxCod.Text);
                    childAdapter.InsertCommand = cmd;
                    childAdapter.SelectCommand.Connection = conn;

                    childAdapter.InsertCommand.ExecuteNonQuery();

                    if (ds.Tables.Contains("Sejururi"))
                        ds.Tables["Sejururi"].Clear();
                    childAdapter.Fill(ds, "Sejururi");

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
                    string updateQuery = "Update Sejururi SET nume_sejur = @nume, detalii_sejur=@detalii_sejur,data_inceput=@data_inceput,data_sfarsit=@data_sfarsit WHERE cod_s=@cod;";

                    SqlCommand cmd = new SqlCommand(updateQuery, conn);
                    cmd.Parameters.AddWithValue("@nume", textBoxNume.Text);
                    cmd.Parameters.AddWithValue("@detalii_sejur", textBoxDetalii.Text);
                    cmd.Parameters.AddWithValue("@data_inceput", textBoxDataIncepere.Text);
                    cmd.Parameters.AddWithValue("@data_sfarsit", textBoxDataSfarsit.Text);
                    cmd.Parameters.AddWithValue("@cod", dataGridViewChild.CurrentRow.Cells["cod_s"].Value.ToString());
                    childAdapter.UpdateCommand = cmd;
                    childAdapter.SelectCommand.Connection = conn;

                    childAdapter.UpdateCommand.ExecuteNonQuery();

                    if (ds.Tables.Contains("Sejururi"))
                        ds.Tables["Sejururi"].Clear();
                    childAdapter.Fill(ds, "Sejururi");

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
                using (SqlConnection conn = new SqlConnection(connectionString))
                {
                    conn.Open();
                    string deleteQuery = "Delete From Sejururi Where cod_s = @cod";
                    SqlCommand cmd = new SqlCommand(deleteQuery, conn);
                    cmd.Parameters.AddWithValue("cod", dataGridViewChild.CurrentRow.Cells["cod_s"].Value.ToString());
                    childAdapter.DeleteCommand = cmd;
                    childAdapter.SelectCommand.Connection = conn;

                    childAdapter.DeleteCommand.ExecuteNonQuery();

                    if (ds.Tables.Contains("Sejururi"))
                        ds.Tables["Sejururi"].Clear();
                    childAdapter.Fill(ds, "Sejururi");
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}