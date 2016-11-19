using System;
using System.Collections;

namespace bOSdotNET_Test
{
	class MainClass
	{
		public static void Main(string[] args)
		{
			/*bOSdotNET.Microsoft.Office.ExcelHelper excel = new bOSdotNET.Microsoft.Office.ExcelHelper(true);

			bOSdotNET.Microsoft.Office.WorkbookHelper workbook1 = excel.OpenFile ("C:\\mySoftware\\Scenario\\ExecutionEnvironment\\database\\dimensionamento pistone MORIS.xls", "",true);

			//set INOUT worksheet
			workbook1.SetWorksheet("INOUT");

			//set array and send it
			object[,] InputPistone=new object[10,1];
			InputPistone[0,0]=350;
			InputPistone[1,0]=0.6;
			InputPistone[2,0]=10000;
			InputPistone[3,0]=100;
			InputPistone[4,0]=100;
			InputPistone[5,0]=1;
			InputPistone[6,0]=1;
			InputPistone[7,0]=100;
			InputPistone[8,0]=100;			
			InputPistone[9,0]=100;
			// non ci sono macro da lanciarelancio la macro per il calcolo
			//string TipoSpinta="C";
			//mExcelAccess.RunMacro(new Object[]{"Foglio1.TipoSpinta",TipoSpinta});
			workbook1.WriteCells ("B4","B13",InputPistone);


			ArrayList _PistoniVerificati=new ArrayList();
			//get INOUT worksheet
			workbook1.SetWorksheet("INOUT");
			string[,] xlsResult=workbook1.ReadCells ("D4","F32");
			//searching verified
			for(int i=0;i<=xlsResult.GetUpperBound(0);i++)
			{
				if(xlsResult[i,2]=="Verificato")
				{
					_PistoniVerificati.Add( xlsResult[i,1] + " x "  + xlsResult[i,0]);
				}
				
			}

			excel.CloseWorkbook (workbook1);
			*/

			bOSdotNET.Microsoft.Office.AccessHelper.RunMacro ("C:\\mySoftware\\ECLift\\DB Design\\Migrazione\\Migrazione.mdb",new Object[] {"OnlyOne"});
		}
	}
}
