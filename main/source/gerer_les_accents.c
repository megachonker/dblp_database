#include <string.h>
#include <stdio.h>
#include <stdlib.h>



//comte le \0
int size(char* string)
{
    int size= 0;
    while(string[size]!='\0')
    {
        size++;
    }
    return size++;
}


void ajouter_la_fin(int i_apres_code, int i_apres_decode, char* string)
{
    int j= i_apres_decode;
    int k= i_apres_code;
    while(string[k]!= '\0')
    {
        string[j]=string[k];
        j++;
        k++;
    }
    string[j]= '\0';
}

void make_decode_string(char decode, char* string, int i_code, int i_apres_code)
{
    string[i_code]= decode;
    ajouter_la_fin(i_code+1, i_apres_code, string);    
}


char* decode_string(char* nom_illisible)
{   
   int i=0;
   while(nom_illisible[i]!='\0')
   {
       if(nom_illisible[i]== '&')
       {
            if(nom_illisible[i+1]=='A')
            {
                if(nom_illisible[i+2]=='g')
                {
                    if(nom_illisible[i+3]=='r'  )
                    {
                        if(nom_illisible[i+4]=='a'  )
                        {
                            if(nom_illisible[i+5]=='v'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        make_decode_string('À', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }
                }
                if(nom_illisible[i+2]=='a')
                {
                    if(nom_illisible[i+3]=='c')
                    {
                        if(nom_illisible[i+4]=='u'  )
                        {
                            if(nom_illisible[i+5]=='t'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&Aacute;", 'Á')
                                        make_decode_string('Á', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='c')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='r'  )
                        {
                            if(nom_illisible[i+5]=='c'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&Acirc;", 'Â')
                                    make_decode_string('Â', nom_illisible, i, i+7);
                                }    
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='t')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {
                            if(nom_illisible[i+5]=='d'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&Atilde;", 'Ã')
                                        make_decode_string('Ã', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='u')
                {
                    if(nom_illisible[i+3]=='m'  )
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {   
                            if(nom_illisible[i+5]==';'  )
                            {     
                                //replace("&Auml;", 'Ä') 
                                make_decode_string('Ä', nom_illisible, i, i+6);     
                            }   
                        }      
                    }     
                }
                if(nom_illisible[i+2]=='r')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='n'  )
                        {
                            if(nom_illisible[i+5]=='g'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&Aring;", 'Å')
                                    make_decode_string('Å', nom_illisible, i, i+7);
                                }    
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='E')
                {
                    if(nom_illisible[i+3]=='l')
                    {
                        if(nom_illisible[i+4]=='i'  )
                        {
                            if(nom_illisible[i+5]=='g'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&AElig;", 'æ')
                                    make_decode_string('æ', nom_illisible, i, i+7);
                                }    
                            }
                        }
                    }  
                }        
            }
            if(nom_illisible[i+1]=='E')
            {
               if(nom_illisible[i+2]=='g')
                {
                    if(nom_illisible[i+3]=='r'  )
                    {
                        if(nom_illisible[i+4]=='a'  )
                        {
                            if(nom_illisible[i+5]=='v'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&Egrave;", 'È')
                                        make_decode_string('È', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }
                }
                if(nom_illisible[i+2]=='a')
                {
                    if(nom_illisible[i+3]=='c')
                    {
                        if(nom_illisible[i+4]=='u'  )
                        {
                            if(nom_illisible[i+5]=='t'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&Eacute;", 'É')
                                        make_decode_string('É', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='c')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='r'  )
                        {
                            if(nom_illisible[i+5]=='c'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&Ecirc;", 'Ê')
                                    make_decode_string('Ê', nom_illisible, i, i+7);
                                }    
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='u')
                {
                    if(nom_illisible[i+3]=='m'  )
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {   
                            if(nom_illisible[i+5]==';'  )
                            {     
                                //replace("&Euml;", 'Ë')  
                                make_decode_string('Ë', nom_illisible, i, i+6);    
                            }   
                        }      
                    }     
                }      
            }
            if(nom_illisible[i+1]=='I')
            {
                if(nom_illisible[i+2]=='g')
                {
                    if(nom_illisible[i+3]=='r'  )
                    {
                        if(nom_illisible[i+4]=='a'  )
                        {
                            if(nom_illisible[i+5]=='v'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&Igrave;", 'Ì')
                                        make_decode_string('Ì', nom_illisible, i, i+8);    
                                    }
                                }
                            }
                        }
                    }
                }
                if(nom_illisible[i+2]=='a')
                {
                    if(nom_illisible[i+3]=='c')
                    {
                        if(nom_illisible[i+4]=='u'  )
                        {
                            if(nom_illisible[i+5]=='t'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&Iacute;", 'Í')
                                        make_decode_string('Í', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='c')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='r'  )
                        {
                            if(nom_illisible[i+5]=='c'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&Icirc;", 'Î')
                                    make_decode_string('Î', nom_illisible, i, i+7);
                                }    
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='u')
                {
                    if(nom_illisible[i+3]=='m'  )
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {   
                            if(nom_illisible[i+5]==';'  )
                            {     
                                //replace("&Iuml;", 'Ï')
                                make_decode_string('Ï', nom_illisible, i, i+6);      
                            }   
                        }      
                    }     
                }             
                 
            }
            if(nom_illisible[i+1]=='O')
            {
                if(nom_illisible[i+2]=='g')
                {
                    if(nom_illisible[i+3]=='r'  )
                    {
                        if(nom_illisible[i+4]=='a'  )
                        {
                            if(nom_illisible[i+5]=='v'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&Ograve;", 'Ò')
                                        make_decode_string('Ò', nom_illisible, i, i+8);  
                                    }
                                }
                            }
                        }
                    }
                }
                if(nom_illisible[i+2]=='a')
                {
                    if(nom_illisible[i+3]=='c')
                    {
                        if(nom_illisible[i+4]=='u'  )
                        {
                            if(nom_illisible[i+5]=='t'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&Oacute;", 'Ó')
                                        make_decode_string('Ó', nom_illisible, i, i+8);  
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='c')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='r'  )
                        {
                            if(nom_illisible[i+5]=='c'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&Ocirc;", 'Ô')
                                    make_decode_string('Ô', nom_illisible, i, i+7);  
                                }    
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='t')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {
                            if(nom_illisible[i+5]=='d'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&Otlde;", 'Õ')
                                        make_decode_string('Õ', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='u')
                {
                    if(nom_illisible[i+3]=='m'  )
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {   
                            if(nom_illisible[i+5]==';'  )
                            {     
                                //replace("&Ouml;", 'Ö') 
                                make_decode_string('Ö', nom_illisible, i, i+6);     
                            }   
                        }      
                    }     
                }
                if(nom_illisible[i+2]=='E')
                {
                    if(nom_illisible[i+3]=='L')
                    {
                        if(nom_illisible[i+4]=='I'  )
                        {
                            if(nom_illisible[i+5]=='G'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&OELIG;", 'Œ')
                                    make_decode_string('Œ', nom_illisible, i, i+7);  
                                }    
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='S')
                {
                    if(nom_illisible[i+3]=='L')
                    {
                        if(nom_illisible[i+4]=='A'  )
                        {
                            if(nom_illisible[i+5]=='S'  )
                            {
                                if(nom_illisible[i+6]=='H'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&OSLASH;", 'Ø')
                                        make_decode_string('Ø', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }  
                }                        
            }
            if(nom_illisible[i+1]=='U')
            {
                if(nom_illisible[i+2]=='g')
                {
                    if(nom_illisible[i+3]=='r'  )
                    {
                        if(nom_illisible[i+4]=='a'  )
                        {
                            if(nom_illisible[i+5]=='v'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&Ugrave;", 'Ù')
                                        make_decode_string('Ù', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }
                }
                if(nom_illisible[i+2]=='a')
                {
                    if(nom_illisible[i+3]=='c')
                    {
                        if(nom_illisible[i+4]=='u'  )
                        {
                            if(nom_illisible[i+5]=='t'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&Uacute;", 'Ú')
                                        make_decode_string('Ú', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='c')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='r'  )
                        {
                            if(nom_illisible[i+5]=='c'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&Ucirc;", 'Û')
                                    make_decode_string('Û', nom_illisible, i, i+7);
                                }    
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='u')
                {
                    if(nom_illisible[i+3]=='m'  )
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {   
                            if(nom_illisible[i+5]==';'  )
                            {     
                                //replace("&Uuml;", 'Ü') 
                                make_decode_string('Ü', nom_illisible, i, i+6);     
                            }   
                        }      
                    }     
                }                    
            }
            if(nom_illisible[i+1]=='Y')
            {
                if(nom_illisible[i+2]=='a')
                {
                    if(nom_illisible[i+3]=='c')
                    {
                        if(nom_illisible[i+4]=='u'  )
                        {
                            if(nom_illisible[i+5]=='t'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&Yacute;", 'Ý')
                                        make_decode_string('Ý', nom_illisible, i, i+8); 
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='u')
                {
                    if(nom_illisible[i+3]=='m'  )
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {   
                            if(nom_illisible[i+5]==';'  )
                            {     
                                //replace("&Yuml;", 'Ÿ') 
                                make_decode_string('Ÿ', nom_illisible, i, i+6);      
                            }   
                        }      
                    }     
                }           
            }
            if(nom_illisible[i+1]=='C')
            {
                if(nom_illisible[i+2]=='c'  )
                {
                    if(nom_illisible[i+3]=='e'  )
                    {
                        if(nom_illisible[i+4]=='d'  )
                        {
                            if(nom_illisible[i+5]=='i'  )
                            {
                                if(nom_illisible[i+6]=='l'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&Ccedil;", 'Ç')
                                        make_decode_string('Ç', nom_illisible, i, i+8); 
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if(nom_illisible[i+1]=='D')
            {
                if(nom_illisible[i+2]=='a')
                {
                    if(nom_illisible[i+3]=='g')
                    {
                        if(nom_illisible[i+4]=='g')
                        {
                            if(nom_illisible[i+5]=='e')
                            {
                                if(nom_illisible[i+6]=='r')
                                {
                                    if(nom_illisible[i+7]==';')
                                    {
                                        //replace("&Dagger;";, '‡')
                                        make_decode_string('‡', nom_illisible, i, i+8); 
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if(nom_illisible[i+1]=='T')
            {
                if(nom_illisible[i+2]=='H'  )
                {
                    if(nom_illisible[i+3]=='O')
                    {
                        if(nom_illisible[i+4]=='R')
                        {
                            if(nom_illisible[i+5]=='N')
                            {
                                if(nom_illisible[i+6]==';')
                                {
                                    //replace("&THORN;";, 'Þ')
                                    make_decode_string('Þ', nom_illisible, i, i+7); 
                                }
                                
                            }
                        }
                    }
                }

            }
            if(nom_illisible[i+1]=='N')
            {
                if(nom_illisible[i+2]=='t')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {
                            if(nom_illisible[i+5]=='d'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&Ntlde;", 'Ñ')
                                        make_decode_string('Ñ', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }  
                }     
            }
            if(nom_illisible[i+1]=='a')
            {
                if(nom_illisible[i+2]=='g')
                {
                    if(nom_illisible[i+3]=='r'  )
                    {
                        if(nom_illisible[i+4]=='a'  )
                        {
                            if(nom_illisible[i+5]=='v'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&agrave;", 'à')
                                        make_decode_string('à', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }
                }
                if(nom_illisible[i+2]=='a')
                {
                    if(nom_illisible[i+3]=='c')
                    {
                        if(nom_illisible[i+4]=='u'  )
                        {
                            if(nom_illisible[i+5]=='t'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&aacute;", 'á')
                                        make_decode_string('á', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='c')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='r'  )
                        {
                            if(nom_illisible[i+5]=='c'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&acirc;", 'â')
                                    make_decode_string('â', nom_illisible, i, i+7);
                                }    
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='t')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {
                            if(nom_illisible[i+5]=='d'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&atlde;", 'ã')
                                        make_decode_string('ã', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='u')
                {
                    if(nom_illisible[i+3]=='m'  )
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {   
                            if(nom_illisible[i+5]==';'  )
                            {     
                                //replace("&auml;", 'ä')
                                make_decode_string('ä', nom_illisible, i, i+6);      
                            }   
                        }      
                    }     
                }
                if(nom_illisible[i+2]=='r')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='n'  )
                        {
                            if(nom_illisible[i+5]=='g'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&aring;", 'å')
                                    make_decode_string('å', nom_illisible, i, i+7);  
                                }    
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='e')
                {
                    if(nom_illisible[i+3]=='l')
                    {
                        if(nom_illisible[i+4]=='i'  )
                        {
                            if(nom_illisible[i+5]=='g'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&aelig;", 'æ')
                                    make_decode_string('æ', nom_illisible, i, i+7);
                                }    
                            }
                        }
                    }  
                }                             
            }
            if(nom_illisible[i+1]=='e')
            {
                if(nom_illisible[i+2]=='u'  )
                {
                    if(nom_illisible[i+2]=='r'  )
                    {
                        if(nom_illisible[i+2]=='o'  )
                        {   
                            if(nom_illisible[i+3]==';'  )
                            {     
                                //replace("&euro;", '€') 
                                make_decode_string('€', nom_illisible, i, i+4);     
                            }   
                        }      
                    }
                }
                if(nom_illisible[i+2]=='g')
                {
                    if(nom_illisible[i+3]=='r'  )
                    {
                        if(nom_illisible[i+4]=='a'  )
                        {
                            if(nom_illisible[i+5]=='v'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&egrave;", 'è')
                                        make_decode_string('è', nom_illisible, i, i+8);  
                                    }
                                }
                            }
                        }
                    }
                }
                if(nom_illisible[i+2]=='a')
                {
                    if(nom_illisible[i+3]=='c')
                    {
                        if(nom_illisible[i+4]=='u'  )
                        {
                            if(nom_illisible[i+5]=='t'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&eacute;", 'é')
                                        make_decode_string('é', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='c')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='r'  )
                        {
                            if(nom_illisible[i+5]=='c'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&ecirc;", 'ê')
                                    make_decode_string('ê', nom_illisible, i, i+7);
                                }    
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='u')
                {
                    if(nom_illisible[i+3]=='m'  )
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {   
                            if(nom_illisible[i+5]==';'  )
                            {     
                                //replace("&euml;", 'ë')
                                make_decode_string('ë', nom_illisible, i, i+6);      
                            }   
                        }      
                    }     
                }                       
            }
            if(nom_illisible[i+1]=='i')
            {
                if(nom_illisible[i+2]=='g')
                {
                    if(nom_illisible[i+3]=='r'  )
                    {
                        if(nom_illisible[i+4]=='a'  )
                        {
                            if(nom_illisible[i+5]=='v'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&igrave;", 'ì')
                                        make_decode_string('ì', nom_illisible, i, i+8);  
                                    }
                                }
                            }
                        }
                    }
                }
                if(nom_illisible[i+2]=='a')
                {
                    if(nom_illisible[i+3]=='c')
                    {
                        if(nom_illisible[i+4]=='u'  )
                        {
                            if(nom_illisible[i+5]=='t'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&iacute;", 'í')
                                        make_decode_string('í', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='u')
                {
                    if(nom_illisible[i+3]=='m'  )
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {   
                            if(nom_illisible[i+5]==';'  )
                            {     
                                //replace("&iuml;", 'ï') 
                                make_decode_string('ï', nom_illisible, i, i+6);     
                            }   
                        }      
                    }     
                }
                if(nom_illisible[i+2]=='e')
                {
                    if(nom_illisible[i+3]=='x')
                    {
                        if(nom_illisible[i+4]=='c'  )
                        {
                            if(nom_illisible[i+5]=='l'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&iexcl;", '¡')
                                    make_decode_string('¡', nom_illisible, i, i+7); 
                                }    
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='q')
                {
                    if(nom_illisible[i+3]=='u')
                    {
                        if(nom_illisible[i+4]=='e'  )
                        {
                            if(nom_illisible[i+5]=='s'  )
                            {
                                if(nom_illisible[i+6]=='t'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&iquest;", '¿')
                                        make_decode_string('¿', nom_illisible, i, i+8); 
                                    }
                                }
                            }
                        }
                    }  
                }           
            }
            if(nom_illisible[i+1]=='o')
            {
                if(nom_illisible[i+2]=='g')
                {
                    if(nom_illisible[i+3]=='r'  )
                    {
                        if(nom_illisible[i+4]=='a'  )
                        {
                            if(nom_illisible[i+5]=='v'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&ograve;", 'ò')
                                        make_decode_string('ò', nom_illisible, i, i+8); 
                                    }
                                }
                            }
                        }
                    }
                }
                if(nom_illisible[i+2]=='a')
                {
                    if(nom_illisible[i+3]=='c')
                    {
                        if(nom_illisible[i+4]=='u'  )
                        {
                            if(nom_illisible[i+5]=='t'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&oacute;", 'ó')
                                        make_decode_string('ó', nom_illisible, i, i+8); 
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='c')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='r'  )
                        {
                            if(nom_illisible[i+5]=='c'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&ocirc;", 'ô')
                                    make_decode_string('ô', nom_illisible, i, i+7); 
                                }    
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='t')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {
                            if(nom_illisible[i+5]=='d'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&otlde;", 'õ')
                                        make_decode_string('õ', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='u')
                {
                    if(nom_illisible[i+3]=='m'  )
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {   
                            if(nom_illisible[i+5]==';'  )
                            {     
                                //replace("&ouml;", 'ö')  
                                make_decode_string('ö', nom_illisible, i, i+6);    
                            }   
                        }      
                    }     
                }
                if(nom_illisible[i+2]=='e')
                {
                    if(nom_illisible[i+3]=='l')
                    {
                        if(nom_illisible[i+4]=='i'  )
                        {
                            if(nom_illisible[i+5]=='g'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&oelig;", 'œ')
                                    make_decode_string('œ', nom_illisible, i, i+7); 
                                }    
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='r')
                {
                    if(nom_illisible[i+3]=='d'  )
                    {
                        if(nom_illisible[i+4]=='m'  )
                        {   
                            if(nom_illisible[i+5]==';'  )
                            {     
                                //replace("&ordm;", 'º') 
                                make_decode_string('º', nom_illisible, i, i+6);      
                            }   
                        }      
                    }     
                }
                if(nom_illisible[i+2]=='r')
                {
                    if(nom_illisible[i+3]=='d'  )
                    {
                        if(nom_illisible[i+4]=='f'  )
                        {   
                            if(nom_illisible[i+5]==';'  )
                            {     
                                //replace("&ordm;", 'ª') 
                                make_decode_string('ª', nom_illisible, i, i+6);     
                            }   
                        }      
                    }     
                }
                if(nom_illisible[i+2]=='s')
                {
                    if(nom_illisible[i+3]=='l')
                    {
                        if(nom_illisible[i+4]=='a'  )
                        {
                            if(nom_illisible[i+5]=='s'  )
                            {
                                if(nom_illisible[i+6]=='h'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&oslash;", 'ø')
                                        make_decode_string('ø', nom_illisible, i, i+8);   
                                    }
                                }
                            }
                        }
                    }  
                }                                                                
            }
            if(nom_illisible[i+1]=='u')
            {
                if(nom_illisible[i+2]=='g')
                {
                    if(nom_illisible[i+3]=='r'  )
                    {
                        if(nom_illisible[i+4]=='a'  )
                        {
                            if(nom_illisible[i+5]=='v'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&ugrave;", 'ù')
                                        make_decode_string('ù', nom_illisible, i, i+8); 
                                    }
                                }
                            }
                        }
                    }
                } 
                if(nom_illisible[i+2]=='a')
                {
                    if(nom_illisible[i+3]=='c')
                    {
                        if(nom_illisible[i+4]=='u'  )
                        {
                            if(nom_illisible[i+5]=='t'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&uacute;", 'ú')
                                        make_decode_string('ú', nom_illisible, i, i+8); 
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='c')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='r'  )
                        {
                            if(nom_illisible[i+5]=='c'  )
                            {
                                if(nom_illisible[i+6]==';'  )
                                {
                                    //replace("&ucirc;", 'û')
                                    make_decode_string('û', nom_illisible, i, i+7); 
                                }    
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='u')
                {
                    if(nom_illisible[i+3]=='m'  )
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {   
                            if(nom_illisible[i+5]==';'  )
                            {     
                                //replace("&uuml;", 'ü') 
                                make_decode_string('ü', nom_illisible, i, i+6);     
                            }   
                        }      
                    }     
                }                  
            }
            if(nom_illisible[i+1]=='y')
            {
                if(nom_illisible[i+2]=='e'  )
                {
                    if(nom_illisible[i+2]=='n'  )
                    {   
                        if(nom_illisible[i+3]==';'  )
                        {     
                            //replace("&yen;", '¥') 
                            make_decode_string('¥', nom_illisible, i, i+4);       
                        }   
                    }      
                }
                if(nom_illisible[i+2]=='a')
                {
                    if(nom_illisible[i+3]=='c')
                    {
                        if(nom_illisible[i+4]=='u'  )
                        {
                            if(nom_illisible[i+5]=='t'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&yacute;", 'ý')
                                        make_decode_string('ý', nom_illisible, i, i+8); 
                                    }
                                }
                            }
                        }
                    }  
                }
                if(nom_illisible[i+2]=='u')
                {
                    if(nom_illisible[i+3]=='m'  )
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {   
                            if(nom_illisible[i+5]==';'  )
                            {     
                                //replace("&yuml;", 'ÿ') 
                                make_decode_string('ÿ', nom_illisible, i, i+6);      
                            }   
                        }      
                    }     
                }           
            }
            if(nom_illisible[i+1]=='c'  )
            {
                if(nom_illisible[i+2]=='c'  )
                {
                    if(nom_illisible[i+3]=='e')
                    {
                        if(nom_illisible[i+4]=='d')
                        {
                            if(nom_illisible[i+5]=='i')
                            {
                                if(nom_illisible[i+6]=='l')
                                {
                                    if(nom_illisible[i+7]==';')
                                    {
                                        //replace("&ccedil;", 'ç')
                                        make_decode_string('ç', nom_illisible, i, i+8); 
                                    }
                                }
                                
                            }
                        }
                    }
                }
                if(nom_illisible[i+2]=='e'  )
                {
                    if(nom_illisible[i+3]=='n')
                    {
                        if(nom_illisible[i+4]=='t')
                        {
                            if(nom_illisible[i+5]==';')
                            {   
                                //replace("&cent;", '¢') 
                                make_decode_string('¢', nom_illisible, i, i+6);  
                            }
                        }
                    }
                }
            }
            if(nom_illisible[i+1]=='s'  )
            {   
                if(nom_illisible[i+2]=='z'  )
                {   
                    if(nom_illisible[i+3]=='l'  )
                    {   
                        if(nom_illisible[i+4]=='i'  )
                        {   
                            if(nom_illisible[i+5]=='g'  )
                            {   
                                if(nom_illisible[i+6]==';'  )
                                {   
                                    //replace("&szlig;", 'ß')
                                    make_decode_string('ß', nom_illisible, i, i+7);
                                }   
                            }   
                        }   
                    }   
                }
                if(nom_illisible[i+2]=='b'  )
                {   
                    if(nom_illisible[i+3]=='q'  )
                    {   
                        if(nom_illisible[i+4]=='u'  )
                        {   
                            if(nom_illisible[i+5]=='o'  )
                            {   
                                if(nom_illisible[i+6]==';'  )
                                {   
                                    //replace("&sbquo;", '‚')
                                    make_decode_string('‚', nom_illisible, i, i+7);
                                }   
                            }   
                        }   
                    }   
                }      
            }
            if(nom_illisible[i+1]=='t'  )
            {  
                if(nom_illisible[i+2]=='h'  )
                {
                    if(nom_illisible[i+3]=='o')
                    {
                        if(nom_illisible[i+4]=='r')
                        {
                            if(nom_illisible[i+5]=='n')
                            {
                                if(nom_illisible[i+6]==';')
                                {
                                    //replace("&thorn;", 'þ')
                                    make_decode_string('þ', nom_illisible, i, i+7);
                                }
                                
                            }
                        }
                    }
                }
                if(nom_illisible[i+2]=='r'  )
                {
                    if(nom_illisible[i+3]=='a')
                    {
                        if(nom_illisible[i+4]=='d')
                        {
                            if(nom_illisible[i+5]=='e')
                            {
                                if(nom_illisible[i+6]==';')
                                {
                                    //replace("&trade;", '™')
                                    make_decode_string('™', nom_illisible, i, i+7);
                                }
                                
                            }
                        }
                    }
                }
            }
            if(nom_illisible[i+1]=='p'  )
            { 
                if(nom_illisible[i+2]=='o'  )
                {
                    if(nom_illisible[i+3]=='u')
                    {
                        if(nom_illisible[i+4]=='n')
                        {
                            if(nom_illisible[i+5]=='d')
                            { 
                                if(nom_illisible[i+6]==';')
                                {
                                    //replace("&pound;", '£')
                                    make_decode_string('£', nom_illisible, i, i+7);
                                }   
                            }
                        }
                    }
                }
            } 
            if(nom_illisible[i+1]== 'n')
            {
                if(nom_illisible[i+2]=='t')
                {
                    if(nom_illisible[i+3]=='i')
                    {
                        if(nom_illisible[i+4]=='l'  )
                        {
                            if(nom_illisible[i+5]=='d'  )
                            {
                                if(nom_illisible[i+6]=='e'  )
                                {
                                    if(nom_illisible[i+7]==';'  )
                                    {
                                        //replace("&ntlde;", 'ñ')
                                        make_decode_string('ñ', nom_illisible, i, i+8);
                                    }
                                }
                            }
                        }
                    }  
                }              
            }
        }
        i++;
   }
   int new_size= size(nom_illisible);
   char* nom_lisible= malloc(sizeof(char)*new_size);
   int k=0;
   while(nom_illisible[k]!='\0')
   {
       nom_lisible[k]=nom_illisible[k];
       k++;
   }
   nom_lisible[k+1]='\0';
   return nom_lisible;
}






int main(void)
{
    char* nom_lisible= decode_string("Fran&ccedil;ois");
    printf("nom lisible: %s\n", nom_lisible);
    free(nom_lisible);
}