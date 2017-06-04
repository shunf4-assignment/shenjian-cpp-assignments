CBigInt CBigInt::Div(CBigInt& A)
{
	CBigInt X, Y, Z;
	int len;
	unsigned __int64 num, div;
	unsigned long carry = 0;
	Y.Mov(*this);
	while (Y.Cmp(A)>0)
	{
		if (Y.m_ulvalue[Y.m_nLength - 1]>A.m_ulvalue[A.m_nLength - 1])
		{
			len = Y.m_nLength - A.m_nLength;
			div = Y.m_ulvalue[Y.m_nLength - 1] / (A.m_ulvalue[A.m_nLength - 1] + 1);
		}
		else if (Y.m_nLength>A.m_nLength)
		{
			len = Y.m_nLength - A.m_nLength - 1;
			num = Y.m_ulvalue[Y.m_nLength - 1];
			num = (num << 32) + Y.m_ulvalue[Y.m_nLength - 2];
			if (A.m_ulvalue[A.m_nLength - 1] == 0xffffffff)div = (num >> 32);
			else div = num / (A.m_ulvalue[A.m_nLength - 1] + 1);
		}
		else
		{
			X.Mov(X.Add(1));
			break;
		}
		Z.Mov(div);
		Z.m_nLength += len;
		for (int i = Z.m_nLength - 1; i >= len; i--)Z.m_ulvalue[i] = Z.m_ulvalue[i - len];
		for (i = 0; i<len; i++)Z.m_ulvalue[i] = 0;
		X.Mov(X.Add(Z));
		Z.Mov(Z.Mul(A));
		Y.Mov(Y.Sub(Z));
	}
	if (Y.Cmp(A) == 0)X.Mov(X.Add(1));
	if (m_nSign + A.m_nSign == 1)X.m_nSign = 0;
	else X.m_nSign = 1;
	return X;
}