using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace bOSdotNET_Test
{
	/// <summary>
	/// Descrizione di riepilogo per Form1.
	/// </summary>
	public class CryptDecryptFile : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox txtTextFile;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Button btnCrypt;
		private System.Windows.Forms.Button btnDecrypt;
		private System.Windows.Forms.Button btnData;
		private System.Windows.Forms.TextBox txtCryptoFile;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox txtKey;
		private System.Windows.Forms.ComboBox cmbCryptAlgorithm;
		private System.Windows.Forms.Label label4;
		/// <summary>
		/// Variabile di progettazione necessaria.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public CryptDecryptFile()
		{
			//
			// Necessario per il supporto di Progettazione Windows Form
			//
			InitializeComponent();

			//
			// TODO: aggiungere il codice del costruttore dopo la chiamata a InitializeComponent
			//
		}

		/// <summary>
		/// Pulire le risorse in uso.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Codice generato da Progettazione Windows Form
		/// <summary>
		/// Metodo necessario per il supporto della finestra di progettazione. Non modificare
		/// il contenuto del metodo con l'editor di codice.
		/// </summary>
		private void InitializeComponent()
		{
			this.txtTextFile = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.txtCryptoFile = new System.Windows.Forms.TextBox();
			this.btnCrypt = new System.Windows.Forms.Button();
			this.btnDecrypt = new System.Windows.Forms.Button();
			this.btnData = new System.Windows.Forms.Button();
			this.label3 = new System.Windows.Forms.Label();
			this.txtKey = new System.Windows.Forms.TextBox();
			this.cmbCryptAlgorithm = new System.Windows.Forms.ComboBox();
			this.label4 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// txtTextFile
			// 
			this.txtTextFile.Location = new System.Drawing.Point(16, 144);
			this.txtTextFile.Name = "txtTextFile";
			this.txtTextFile.Size = new System.Drawing.Size(320, 22);
			this.txtTextFile.TabIndex = 0;
			this.txtTextFile.Text = "";
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(16, 120);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(320, 24);
			this.label1.TabIndex = 1;
			this.label1.Text = "File in formato testo";
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(16, 184);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(320, 24);
			this.label2.TabIndex = 3;
			this.label2.Text = "File Crittografato";
			// 
			// txtCryptoFile
			// 
			this.txtCryptoFile.Location = new System.Drawing.Point(16, 208);
			this.txtCryptoFile.Name = "txtCryptoFile";
			this.txtCryptoFile.Size = new System.Drawing.Size(320, 22);
			this.txtCryptoFile.TabIndex = 2;
			this.txtCryptoFile.Text = "";
			// 
			// btnCrypt
			// 
			this.btnCrypt.Location = new System.Drawing.Point(360, 144);
			this.btnCrypt.Name = "btnCrypt";
			this.btnCrypt.Size = new System.Drawing.Size(176, 24);
			this.btnCrypt.TabIndex = 4;
			this.btnCrypt.Text = "Crypt";
			this.btnCrypt.Click += new System.EventHandler(this.btnCrypt_Click);
			// 
			// btnDecrypt
			// 
			this.btnDecrypt.Location = new System.Drawing.Point(360, 208);
			this.btnDecrypt.Name = "btnDecrypt";
			this.btnDecrypt.Size = new System.Drawing.Size(184, 24);
			this.btnDecrypt.TabIndex = 5;
			this.btnDecrypt.Text = "Decrypt";
			this.btnDecrypt.Click += new System.EventHandler(this.btnDecrypt_Click);
			// 
			// btnData
			// 
			this.btnData.Location = new System.Drawing.Point(360, 96);
			this.btnData.Name = "btnData";
			this.btnData.Size = new System.Drawing.Size(176, 24);
			this.btnData.TabIndex = 4;
			this.btnData.Text = "Enter Data";
			this.btnData.Click += new System.EventHandler(this.btnData_Click);
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(16, 72);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(320, 24);
			this.label3.TabIndex = 7;
			this.label3.Text = "Key";
			// 
			// txtKey
			// 
			this.txtKey.Location = new System.Drawing.Point(16, 96);
			this.txtKey.Name = "txtKey";
			this.txtKey.Size = new System.Drawing.Size(320, 22);
			this.txtKey.TabIndex = 6;
			this.txtKey.Text = "";
			// 
			// cmbCryptAlgorithm
			// 
			this.cmbCryptAlgorithm.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cmbCryptAlgorithm.Items.AddRange(new object[] {
																   "XOR256Stream"});
			this.cmbCryptAlgorithm.Location = new System.Drawing.Point(16, 32);
			this.cmbCryptAlgorithm.Name = "cmbCryptAlgorithm";
			this.cmbCryptAlgorithm.Size = new System.Drawing.Size(312, 24);
			this.cmbCryptAlgorithm.TabIndex = 8;
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(16, 8);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(320, 24);
			this.label4.TabIndex = 9;
			this.label4.Text = "Crypting Algorithm";
			// 
			// CryptDecryptFile
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 15);
			this.ClientSize = new System.Drawing.Size(568, 251);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.cmbCryptAlgorithm);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.txtKey);
			this.Controls.Add(this.btnDecrypt);
			this.Controls.Add(this.btnCrypt);
			this.Controls.Add(this.btnData);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.txtCryptoFile);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.txtTextFile);
			this.Name = "CryptDecryptFile";
			this.Text = "CryptDecryptFile";
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// Il punto di ingresso principale dell'applicazione.
		/// </summary>
		[STAThread]
		/*
		static void Main() 
		{
			Application.Run(new CryptDecryptFile());
		}
		*/

		private void btnCrypt_Click(object sender, System.EventArgs e)
		{
			int iRet = bOSdotNET.Crypto.XOR256Stream.EncryptFile (txtKey.Text, txtTextFile.Text, txtCryptoFile.Text);

			if ( iRet == 0 )
			{
				System.Windows.Forms.MessageBox.Show ("File Crypted", "Crypting");
			}
			else
			{
				System.Windows.Forms.MessageBox.Show ("File Not Crypted", "Crypting" );
			}
		}

		private void btnDecrypt_Click(object sender, System.EventArgs e)
		{
			int iRet = bOSdotNET.Crypto.XOR256Stream.DecryptFile (txtKey.Text,txtCryptoFile.Text, txtTextFile.Text);

			if ( iRet == 0 )
			{
				System.Windows.Forms.MessageBox.Show ("File decrypted.", "Decrypting");
			}
			else
			{
				System.Windows.Forms.MessageBox.Show ("File not decrypted.", "Decrypting" );
			}
		
		}
		private void btnData_Click(object sender, System.EventArgs e)
		{
			CryptDecryptString form2 = new CryptDecryptString();
			form2.Show();
		}
	}
}
