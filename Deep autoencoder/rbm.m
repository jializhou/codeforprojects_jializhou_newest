% Version 1.000 
%
% Code provided by Geoff Hinton and Ruslan Salakhutdinov 
%
% Permission is granted for anyone to copy, use, modify, or distribute this
% program and accompanying programs and documents for any purpose, provided
% this copyright notice is retained and prominently displayed, along with
% a note saying that the original programs are available from our
% web page.
% The programs and documents are distributed without any warranty, express or
% implied.  As the programs were written for research purposes only, they have
% not been tested to the degree that would be advisable in any important
% application.  All use of these programs is entirely at the user's own risk.

% This program trains Restricted Boltzmann Machine in which
% visible, binary, stochastic pixels are connected to
% hidden, binary, stochastic feature detectors using symmetrically
% weighted connections. Learning is done with 1-step Contrastive Divergence.   
% The program assumes that the following variables are set externally:
% maxepoch  -- maximum number of epochs
% numhid    -- number of hidden units 
% batchdata -- the data that is divided into batches (numcases numdims numbatches)
% restart   -- set to 1 if learning starts from beginning 

epsilonw      = 0.1;   % Learning rate for weights 
epsilonvb     = 0.1;   % Learning rate for biases of visible units 
epsilonhb     = 0.1;   % Learning rate for biases of hidden units 
weightcost  = 0.0002;   
initialmomentum  = 0.5;
finalmomentum    = 0.9;

[numcases numdims numbatches]=size(batchdata);

if restart ==1,
	restart=0;
	epoch=1;

	% Initializing symmetric weights and biases. 初始化对称权值和偏置
	vishid = 0.1*randn(numdims, numhid); %初始化生成可视层到隐藏层的权值
	hidbiases = zeros(1,numhid);%隐藏单元的偏置值
	visbiases = zeros(1,numdims);%可见单元的偏置值

	poshidprobs = zeros(numcases,numhid); %正向的隐藏单元概率生成
	neghidprobs = zeros(numcases,numhid);%反向的隐藏单元概率生成
	posprods = zeros(numdims,numhid);
	negprods = zeros(numdims,numhid);
	vishidinc = zeros(numdims,numhid);%可视单元和隐藏单元之间的权值增量
	hidbiasinc = zeros(1,numhid);%隐藏单元的偏置增量
	visbiasinc = zeros(1,numdims);%可视单元的偏置增量
	batchposhidprobs=zeros(numcases,numhid,numbatches);%存储每次迭代计算好的每层的隐藏层概率，作为下一个RBM的输入
end

for epoch = epoch:maxepoch,
 fprintf(1,'epoch %d\r',epoch); 
 errsum=0;
 for batch = 1:numbatches,
		fprintf(1,'epoch %d batch %d\r',epoch,batch); 

		%%%%%%%%% START POSITIVE PHASE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
		data = batchdata(:,:,batch); %读取当前批次的全部数据vi
		poshidprobs = 1./(1 + exp(-data*vishid - repmat(hidbiases,numcases,1))); %计算前向传播的隐藏层概率hi
		batchposhidprobs(:,:,batch)=poshidprobs; %将计算好的概率赋值给当前批次前向传播的隐藏层最后一次计算好的值作为下一层的输入
		posprods = data' * poshidprobs; %contrastive divergence过程<vi,hi>

		poshidact = sum(poshidprobs);%average-wise隐藏层激活概率值
		posvisact = sum(data);%average-wise可视层激活概率值

		%%%%%%%%% END OF POSITIVE PHASE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		poshidstates = poshidprobs > rand(numcases,numhid);%gibbs抽样,设定状态

		%It is very important to make these hidden states binary, rather than using the probabilities
		%themselves. If the probabilities are used, each hidden unit can communicate a real-value to the
		%visible units during the reconstruction. This seriously violates the information bottleneck created by
		%the fact that a hidden unit can convey at most one bit (on average). This information bottleneck
		%acts as a strong regularizer.
		
		%%%%%%%%% START NEGATIVE PHASE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		negdata = 1./(1 + exp(-poshidstates*vishid' - repmat(visbiases,numcases,1)));%根据hi计算vi+1
		neghidprobs = 1./(1 + exp(-negdata*vishid - repmat(hidbiases,numcases,1))); %根据vi+1计算hi+1
		negprods = negdata'*neghidprobs;%contrastive divergence <vi+1,hi+1>

		neghidact = sum(neghidprobs);
		negvisact = sum(negdata);
		%%%%%%%%% END OF NEGATIVE PHASE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		%However, it is common to use the probability, pi, instead of sampling a binary value. This is not
		%nearly as problematic as using probabilities for the data-driven hidden states and it reduces sampling
		%noise thus allowing faster learning. There is some evidence that it leads to slightly worse density
		%models (Tijmen Tieleman, personal communication, 2008). This probably does not matter when
		%using an RBM to pretrain a layer of hidden features for use in a deep belief net.

		err= sum(sum( (data-negdata).^2 ));
		errsum = err + errsum;
	    if epoch>5,
			momentum=finalmomentum;
		else
			momentum=initialmomentum;
		end;

		%%%%%%%%% UPDATE WEIGHTS AND BIASES %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
		vishidinc = momentum*vishidinc + ...
					epsilonw*( (posprods-negprods)/numcases - weightcost*vishid);
		visbiasinc = momentum*visbiasinc + (epsilonvb/numcases)*(posvisact-negvisact);
		hidbiasinc = momentum*hidbiasinc + (epsilonhb/numcases)*(poshidact-neghidact);

		vishid = vishid + vishidinc;
		visbiases = visbiases + visbiasinc;
		hidbiases = hidbiases + hidbiasinc;

		%%%%%%%%%%%%%%%% END OF UPDATES %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 

	  end
  fprintf(1, 'epoch %4i error %6.1f  \n', epoch, errsum); 
end;
