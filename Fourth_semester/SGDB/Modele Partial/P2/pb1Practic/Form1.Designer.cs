namespace pb1Practic
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            dataGridViewParent = new DataGridView();
            dataGridViewChild = new DataGridView();
            textBoxNume = new TextBox();
            label1 = new Label();
            label2 = new Label();
            textBoxDescriere = new TextBox();
            label3 = new Label();
            textBoxPret = new TextBox();
            buttonAdd = new Button();
            buttonModifica = new Button();
            buttonSterge = new Button();
            label4 = new Label();
            textBoxCod = new TextBox();
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).BeginInit();
            SuspendLayout();
            // 
            // dataGridViewParent
            // 
            dataGridViewParent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewParent.Location = new Point(12, 32);
            dataGridViewParent.Name = "dataGridViewParent";
            dataGridViewParent.RowHeadersWidth = 51;
            dataGridViewParent.RowTemplate.Height = 29;
            dataGridViewParent.Size = new Size(497, 329);
            dataGridViewParent.TabIndex = 0;
            // 
            // dataGridViewChild
            // 
            dataGridViewChild.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewChild.Location = new Point(544, 32);
            dataGridViewChild.Name = "dataGridViewChild";
            dataGridViewChild.RowHeadersWidth = 51;
            dataGridViewChild.RowTemplate.Height = 29;
            dataGridViewChild.Size = new Size(651, 329);
            dataGridViewChild.TabIndex = 1;
            // 
            // textBoxNume
            // 
            textBoxNume.Location = new Point(103, 392);
            textBoxNume.Name = "textBoxNume";
            textBoxNume.Size = new Size(162, 27);
            textBoxNume.TabIndex = 2;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(33, 395);
            label1.Name = "label1";
            label1.Size = new Size(49, 20);
            label1.TabIndex = 3;
            label1.Text = "Nume";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(33, 447);
            label2.Name = "label2";
            label2.Size = new Size(71, 20);
            label2.TabIndex = 5;
            label2.Text = "Descriere";
            // 
            // textBoxDescriere
            // 
            textBoxDescriere.Location = new Point(103, 444);
            textBoxDescriere.Name = "textBoxDescriere";
            textBoxDescriere.Size = new Size(162, 27);
            textBoxDescriere.TabIndex = 4;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(33, 491);
            label3.Name = "label3";
            label3.Size = new Size(35, 20);
            label3.TabIndex = 7;
            label3.Text = "Pret";
            // 
            // textBoxPret
            // 
            textBoxPret.Location = new Point(103, 488);
            textBoxPret.Name = "textBoxPret";
            textBoxPret.Size = new Size(162, 27);
            textBoxPret.TabIndex = 6;
            textBoxPret.TextChanged += textBox1_TextChanged;
            // 
            // buttonAdd
            // 
            buttonAdd.Location = new Point(342, 389);
            buttonAdd.Name = "buttonAdd";
            buttonAdd.Size = new Size(94, 29);
            buttonAdd.TabIndex = 8;
            buttonAdd.Text = "Adauga";
            buttonAdd.UseVisualStyleBackColor = true;
            buttonAdd.Click += buttonAdd_Click;
            // 
            // buttonModifica
            // 
            buttonModifica.Location = new Point(346, 440);
            buttonModifica.Name = "buttonModifica";
            buttonModifica.Size = new Size(94, 29);
            buttonModifica.TabIndex = 9;
            buttonModifica.Text = "Modifica";
            buttonModifica.UseVisualStyleBackColor = true;
            buttonModifica.Click += buttonModifica_Click;
            // 
            // buttonSterge
            // 
            buttonSterge.Location = new Point(346, 492);
            buttonSterge.Name = "buttonSterge";
            buttonSterge.Size = new Size(94, 29);
            buttonSterge.TabIndex = 10;
            buttonSterge.Text = "Sterge";
            buttonSterge.UseVisualStyleBackColor = true;
            buttonSterge.Click += buttonSterge_Click;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(33, 549);
            label4.Name = "label4";
            label4.Size = new Size(59, 20);
            label4.TabIndex = 12;
            label4.Text = "CodCof";
            // 
            // textBoxCod
            // 
            textBoxCod.Location = new Point(103, 546);
            textBoxCod.Name = "textBoxCod";
            textBoxCod.ReadOnly = true;
            textBoxCod.Size = new Size(162, 27);
            textBoxCod.TabIndex = 11;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1193, 677);
            Controls.Add(label4);
            Controls.Add(textBoxCod);
            Controls.Add(buttonSterge);
            Controls.Add(buttonModifica);
            Controls.Add(buttonAdd);
            Controls.Add(label3);
            Controls.Add(textBoxPret);
            Controls.Add(label2);
            Controls.Add(textBoxDescriere);
            Controls.Add(label1);
            Controls.Add(textBoxNume);
            Controls.Add(dataGridViewChild);
            Controls.Add(dataGridViewParent);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private DataGridView dataGridViewParent;
        private DataGridView dataGridViewChild;
        private TextBox textBoxNume;
        private Label label1;
        private Label label2;
        private TextBox textBoxDescriere;
        private Label label3;
        private TextBox textBoxPret;
        private Button buttonAdd;
        private Button buttonModifica;
        private Button buttonSterge;
        private Label label4;
        private TextBox textBoxCod;
    }
}