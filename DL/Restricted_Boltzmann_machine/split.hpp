void split_(const char* str,const char split_char,vector<uint32_t>& str_v)
{
        const char* term_head = str;
        const char* term_tail = str;
        for(;(term_head = term_tail )!='\0';)
        {
                string os ;
                char buf[2];
                buf[1]='\0';
                for(term_tail = term_head; *term_tail != split_char&&*term_tail!='\0'&&*term_tail!='\n' ;term_tail++)
                {
                        buf[0] = *term_tail;
                        os.append(buf);
                }
                if(*term_tail == split_char)
                {
                        str_v.push_back(atoi(os.c_str()));
                        term_tail++;
                }
                else if(*term_tail == '\n')
                {
                          str_v.push_back(atoi(os.c_str()));
                        return;
                }
                else if(*term_tail == '\0')
                {
                        str_v.push_back(atoi(os.c_str()));
                        return;
                }
                else
                        return;
        }

};
