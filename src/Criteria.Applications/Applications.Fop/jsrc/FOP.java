//Java
import java.io.*;
import java.io.File;
import java.io.IOException;
import java.io.OutputStream;

//JAXP
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.TransformerException;
import javax.xml.transform.Source;
import javax.xml.transform.Result;
import javax.xml.transform.stream.StreamSource;
import javax.xml.transform.sax.SAXResult;

//Avalon
import org.apache.avalon.framework.ExceptionUtil;
import org.apache.avalon.framework.logger.ConsoleLogger;
import org.apache.avalon.framework.logger.Logger;

//FOP
import org.apache.fop.apps.Driver;
import org.apache.fop.apps.FOPException;
import org.apache.fop.messaging.MessageHandler;

public class FOP
{
    static public void convertXML2PDF(File xml, File xslt, File pdf) 
    {
        //Construct driver
        Driver driver = new Driver();
        
        //Setup logger
        Logger logger = new ConsoleLogger(ConsoleLogger.LEVEL_INFO);
        driver.setLogger(logger);
        MessageHandler.setScreenLogger(logger);

        //Setup Renderer (output format)        
        driver.setRenderer(Driver.RENDER_PDF);
        
        //Setup output
        try
        {
        	OutputStream out = new java.io.FileOutputStream(pdf);
        
            driver.setOutputStream(out);

            //Setup XSLT
            TransformerFactory factory = TransformerFactory.newInstance();
            Transformer transformer = factory.newTransformer(new StreamSource(xslt));
        
            //Setup input for XSLT transformation
            Source src = new StreamSource(xml);
        
            //Resulting SAX events (the generated FO) must be piped through to FOP
            Result res = new SAXResult(driver.getContentHandler());

            //Start XSLT transformation and FOP processing
            transformer.transform(src, res);
            
            out.close();
        }
        catch  (java.io.FileNotFoundException fnfErr)
        {
        	System.out.println("FileNotFound");	
        }
        catch ( javax.xml.transform.TransformerConfigurationException tcErr) 
        {
			System.out.println("TransformerConfigurationException");	
        }
        catch ( javax.xml.transform.TransformerException tErr) 
        {
        	System.out.println("TransformerException");
        }
        catch ( java.io.IOException err)
        {
        	System.out.println("IOException");	
        }
        finally
        {
        }
    }
    
    static  public void convertXML2PDF(String sXml, String sXsl, String sPdf) 
	{    
        //Setup input and output files            
        File xmlfile = new File(sXml);
        File xsltfile = new File(sXsl);
        File pdffile = new File(sPdf);

		FOP.convertXML2PDF(xmlfile, xsltfile, pdffile);
    }
    
    static public void convertXML2PDF(String[] vFiles)
    {
    	FOP.convertXML2PDF(vFiles[0], vFiles[1], vFiles[2]);
    }
    
	public static void main(String[] args) 
    {
        try
        {
            System.out.println("Preparing...");

            //Setup input and output files            
            File xmlfile = new File(args[0]);
            File xsltfile = new File(args[1]);
            File pdffile = new File(args[2]);

            System.out.println("Input: XML (" + xmlfile + ")");
            System.out.println("Stylesheet: " + xsltfile);
            System.out.println("Output: PDF (" + pdffile + ")");
            System.out.println();
            System.out.println("Transforming...");
            
            FOP app = new FOP();
            app.convertXML2PDF(xmlfile, xsltfile, pdffile);
            
            System.out.println("Success!");
        }
        catch (Exception e)
        {
            System.out.println(ExceptionUtil.printStackTrace(e));
            System.exit(-1);
        }
    }
}
