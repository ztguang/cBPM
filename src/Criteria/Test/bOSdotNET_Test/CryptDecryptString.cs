using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace bOSdotNET_Test
{
	/// <summary>
	/// Descrizione di riepilogo per CryptDecryptString.
	/// </summary>
	public class CryptDecryptString : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox txtText;
		private System.Windows.Forms.TextBox txtTextAfter;
		private System.Windows.Forms.TextBox txtCrypto;
		private System.Windows.Forms.Button btnEncrypt;
		private System.Windows.Forms.Button btnDecrypt;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox txtKey;
		/// <summary>
		/// Variabile di progettazione necessaria.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public CryptDecryptString()
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
				if(components != null)
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
			this.txtText = new System.Windows.Forms.TextBox();
			this.txtTextAfter = new System.Windows.Forms.TextBox();
			this.txtCrypto = new System.Windows.Forms.TextBox();
			this.btnEncrypt = new System.Windows.Forms.Button();
			this.btnDecrypt = new System.Windows.Forms.Button();
			this.label3 = new System.Windows.Forms.Label();
			this.txtKey = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// txtText
			// 
			this.txtText.Location = new System.Drawing.Point(16, 72);
			this.txtText.Multiline = true;
			this.txtText.Name = "txtText";
			this.txtText.Size = new System.Drawing.Size(336, 288);
			this.txtText.TabIndex = 0;
			this.txtText.Text = "";
			// 
			// txtTextAfter
			// 
			this.txtTextAfter.Location = new System.Drawing.Point(376, 72);
			this.txtTextAfter.Multiline = true;
			this.txtTextAfter.Name = "txtTextAfter";
			this.txtTextAfter.Size = new System.Drawing.Size(336, 288);
			this.txtTextAfter.TabIndex = 1;
			this.txtTextAfter.Text = "";
			// 
			// txtCrypto
			// 
			this.txtCrypto.Location = new System.Drawing.Point(24, 392);
			this.txtCrypto.Multiline = true;
			this.txtCrypto.Name = "txtCrypto";
			this.txtCrypto.Size = new System.Drawing.Size(688, 168);
			this.txtCrypto.TabIndex = 2;
			this.txtCrypto.Text = "";
			// 
			// btnEncrypt
			// 
			this.btnEncrypt.Location = new System.Drawing.Point(24, 592);
			this.btnEncrypt.Name = "btnEncrypt";
			this.btnEncrypt.Size = new System.Drawing.Size(232, 32);
			this.btnEncrypt.TabIndex = 3;
			this.btnEncrypt.Text = "Encrypt";
			this.btnEncrypt.Click += new System.EventHandler(this.btnEncrypt_Click);
			// 
			// btnDecrypt
			// 
			this.btnDecrypt.Location = new System.Drawing.Point(480, 592);
			this.btnDecrypt.Name = "btnDecrypt";
			this.btnDecrypt.Size = new System.Drawing.Size(232, 32);
			this.btnDecrypt.TabIndex = 4;
			this.btnDecrypt.Text = "Decrypt";
			this.btnDecrypt.Click += new System.EventHandler(this.btnDecrypt_Click);
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(16, 16);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(320, 24);
			this.label3.TabIndex = 10;
			this.label3.Text = "Key";
			// 
			// txtKey
			// 
			this.txtKey.Location = new System.Drawing.Point(16, 40);
			this.txtKey.Name = "txtKey";
			this.txtKey.Size = new System.Drawing.Size(320, 22);
			this.txtKey.TabIndex = 9;
			this.txtKey.Text = "";
			// 
			// CryptDecryptString
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 15);
			this.ClientSize = new System.Drawing.Size(728, 651);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.txtKey);
			this.Controls.Add(this.btnDecrypt);
			this.Controls.Add(this.btnEncrypt);
			this.Controls.Add(this.txtCrypto);
			this.Controls.Add(this.txtTextAfter);
			this.Controls.Add(this.txtText);
			this.Name = "CryptDecryptString";
			this.Text = "CryptDecryptString";
			this.ResumeLayout(false);

		}
		#endregion

		private void btnEncrypt_Click(object sender, System.EventArgs e)
		{
			String sKey=txtKey.Text;
			String sIn= txtText.Text;
			txtCrypto.Text = bOSdotNET.Crypto.XOR256Stream.EncryptString (sKey, sIn);
		}

		private void btnDecrypt_Click(object sender, System.EventArgs e)
		{
			txtTextAfter.Text  = bOSdotNET.Crypto.XOR256Stream.DecryptString (txtKey.Text,txtCrypto.Text);
		}
	}
}
